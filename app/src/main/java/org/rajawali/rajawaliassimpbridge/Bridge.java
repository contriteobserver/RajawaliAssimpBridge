package org.rajawali.rajawaliassimpbridge;

import android.content.res.AssetManager;
import android.graphics.Color;
import android.util.Log;

import org.rajawali3d.Object3D;
import org.rajawali3d.animation.Animation;
import org.rajawali3d.animation.AnimationGroup;
import org.rajawali3d.animation.SplineTranslateAnimation3D;
import org.rajawali3d.curves.CatmullRomCurve3D;
import org.rajawali3d.lights.ALight;
import org.rajawali3d.lights.DirectionalLight;
import org.rajawali3d.materials.Material;
import org.rajawali3d.materials.methods.DiffuseMethod;
import org.rajawali3d.materials.methods.SpecularMethod;
import org.rajawali3d.math.Quaternion;
import org.rajawali3d.math.vector.Vector3;

public class Bridge {
    private static final aiShadingModel[] ShadingModelValues = aiShadingModel.values();

    // Used to load the bridge library on application startup.
    static {
        System.loadLibrary("bridgeJNI");
    }

    static String getVersion() { return getJNIversion();}
    static long createImporter(AssetManager assetManager) { return createJNIimporter(assetManager); }
    static long readFile(long importer, String path) { return readJNIfile(importer, path); }
    static String errorMessage(long importer) { return errorJNImessage(importer); }
    static void freeScene(long importer) { freeJNIscene(importer); }
    static void destroyImporter(long importer) { destroyJNIimporter(importer); }

    static long getNumMeshes(long scene) { return getNumJNImeshes(scene); }
    static long getNumTextures(long scene) { return getNumJNItextures(scene); }
    static long getNumLights(long scene) { return getNumJNIlights(scene); }
    static long getNumCameras(long scene) { return getNumJNIcameras(scene); }
    static long getNumAnimations(long scene) { return getNumJNIanimations(scene); }

    static Object3D getObjAt(long scene, int index) {
        float[] vertices = getJNIvertices(scene, index);
        float[] normals = getJNInormals(scene, index);
        float[] colors = getJNIcolors(scene, index);
        float[] textureCoords  = getJNItextureCoords(scene, index);
        int[] indices = getJNIindices(scene, index);

        Object3D obj = new Object3D();
        obj.setData(vertices, normals, textureCoords, colors, indices, true);
        obj.setName(getJNImeshName(scene, index));
        obj.setDoubleSided(getJNIdoubleSided(scene, getMaterialIndex(scene, index)));
        return obj;
    }

    static int getMaterialIndex(long scene, int index) {
        return getJNImaterialIndex(scene, index);
    }

    static Material getMaterialAt(long scene, int index) {
        float[] rgba = getJNIspecularRGBA(scene, index);
        float shininess = getJNIshininess(scene, index);
        float intensity =  getJNIstrength(scene, index);
        int specularColor = Color.argb(
                Math.round(0xff*rgba[3]),
                Math.round(0xff*rgba[0]),
                Math.round(0xff*rgba[1]),
                Math.round(0xff*rgba[2])
        );

        Log.i("Bridge.getMaterialAt", "name: " + getJNImaterialName(scene, index));
        Log.i("Bridge.getMaterialAt", "shading model: " + ShadingModelValues[getJNIshadingModel(scene, index)]);
        Log.i("Bridge.getMaterialAt", "enable wireframe: " + enableJNIwireframe(scene, index));

        Material material = new Material();
        material.setColor(getJNIdiffuseRGBA(scene, index));
        material.setColorInfluence(getJNIopacity(scene, index));
        material.setAmbientColor(getJNIambientRGBA(scene, index));
        material.setDiffuseMethod(new DiffuseMethod.Lambert());
        material.setSpecularMethod(new SpecularMethod.Phong(specularColor, shininess, intensity));
        material.enableLighting(true);
        return material;
    }

    static ALight getLightAt(long scene, int index) {
        float[] buf;
        ALight light = null;
        switch(getJNIlightType(scene, index)) {
            default:
                buf = getJNIlightDirection(scene, index);
                light = new DirectionalLight(buf[0], buf[1], buf[2]);
                buf = getJNIlightPosition(scene, index);
                light.setPosition(buf[0], buf[1], buf[2]);
                buf = getJNIlightDiffuseRGB(scene, index);
                light.setColor(buf[0], buf[1], buf[2]);
                light.setPower(5/4f);
                break;
        }
        return light;
    }

    static AnimationGroup getAnimationFor(Object3D obj, long scene, int index) {
        float keyFrames[];
        AnimationGroup group = new AnimationGroup();

        Log.i("Bridge.getAnimationAt", "name: " + getJNIanimationName(scene, index));
        Log.i("Bridge.getAnimationAt", "duration: " + getJNIanimationDuration(scene, index));
        Log.i("Bridge.getAnimationAt", "translation length: " + getJNItranslationKeyframes(scene, index).length/4);
        Log.i("Bridge.getAnimationAt", "orientation length: " + getJNIorientationKeyframes(scene, index).length/5);
        Log.i("Bridge.getAnimationAt", "scaling length: " + getJNIscalingKeyframes(scene, index).length/4);
        Log.i("Bridge.getAnimationAt", "morph poses: " + getJNInumAnimeshes(scene, index));
        Log.i("Bridge.getAnimationAt", "morph keyframe length: " + getJNInumMorphKeyFrames(scene, index));

        keyFrames = getJNItranslationKeyframes(scene, index);
        if(keyFrames.length > 0) {
            Path3D path = new Path3D();
            for(int i=0; i<keyFrames.length; i+=4) {
                path.addPoint(new Vector3(keyFrames[i+1], keyFrames[i+2], keyFrames[i+3]));
            }
            path.isClosedCurve(true);
            SplineTranslateAnimation3D translation = new SplineTranslateAnimation3D(path);
            translation.setDurationDelta(getJNIanimationDuration(scene, index));
            translation.setTransformable3D(obj);
            group.addAnimation(translation);
        }

        keyFrames = getJNIorientationKeyframes(scene, index);
        if(keyFrames.length > 0) {
            Path4D path = new Path4D();
            for(int i=0; i<keyFrames.length; i+=5) {
                path.addPoint(new Quaternion(keyFrames[i+1], keyFrames[i+2], keyFrames[i+3], keyFrames[i+4]));
            }
            path.isClosedCurve(true);
            SplineOrientationAnimation3D translation = new SplineOrientationAnimation3D(path);
            translation.setDurationDelta(getJNIanimationDuration(scene, index));
            translation.setTransformable3D(obj);
            group.addAnimation(translation);
        }

        keyFrames = getJNIscalingKeyframes(scene, index);
        if(keyFrames.length > 0) {
            Path3D path = new Path3D();
            for(int i=0; i<keyFrames.length; i+=4) {
                path.addPoint(new Vector3(keyFrames[i+1], keyFrames[i+2], keyFrames[i+3]));
            }
            path.isClosedCurve(true);
            SplineScalingAnimation3D scaling = new SplineScalingAnimation3D(path);
            scaling.setDurationDelta(getJNIanimationDuration(scene, index));
            scaling.setTransformable3D(obj);
            group.addAnimation(scaling);
        }

        int numKeyFrames = getJNInumMorphKeyFrames(scene, index);
        if(numKeyFrames > 0) {
            int vertices[] = getJNImorphVertices(scene, index);
            double weights[]  = getJNImorphVertexWeights(scene, index);
            Log.i("Bridge.getAnimationAt", "morph vertices: " + vertices);
            Log.i("Bridge.getAnimationAt", "morph vertices: " + weights);
        }

        group.setDurationDelta(getJNIanimationDuration(scene, index));
        group.setRepeatMode(Animation.RepeatMode.INFINITE);
        return group;
    }

    static float getOpacity(long scene, int index) { return getJNIopacity(scene, index); }
    static float getTransparency(long scene, int index) { return getJNItransparency(scene, index); }

    static boolean hasAmbientTexture(long scene, int index) { return hasJNIambientTexture(scene, index); }
    static boolean hasDiffuseTexture(long scene, int index) { return hasJNIdiffuseTexture(scene, index); }
    static boolean hasSpecularTexture(long scene, int index) { return hasJNIspecularTexture(scene, index); }
    static boolean hasNormalMap(long scene, int index) { return hasJNInormalMap(scene, index); }

    static String getAmbientName(long scene, int index) { return getJNIambientName(scene, index); }
    static String getDiffuseName(long scene, int index) { return getJNIdiffuseName(scene,index); }
    static String getSpecularName(long scene, int index) { return getJNIspecularName(scene, index); }
    static String getNormalMapName(long scene, int index) { return getJNInormalMapName(scene, index); }

    static String getEmbeddedLabel(long scene, String label) { return getJNIembeddedLabel(scene,label); }
    static int getEmbeddedOffset(long scene, String label) { return getJNIembeddedOffset(scene,label); }
    static int getEmbeddedLength(long scene, String label) { return getJNIembeddedLength(scene,label); }
    static byte[] getEmbeddedBytes(long scene, String label) { return getJNIembeddedBytes(scene,label); }

    //
    // native methods implemented in the packaged 'bridge' library.
    //
    private static native String getJNIversion();
    private static native long createJNIimporter(AssetManager assetManager);
    private static native long readJNIfile(long importer, String path);
    private static native String errorJNImessage(long importer);
    private static native void freeJNIscene(long importer);
    private static native void destroyJNIimporter(long importer);

    private static native long getNumJNImeshes(long scene);
    private static native long getNumJNItextures(long scene);
    private static native long getNumJNIlights(long scene);
    private static native long getNumJNIcameras(long scene);
    private static native long getNumJNIanimations(long scene);

    // methods indexed by mesh
    private static native float[] getJNIvertices(long scene, int index);
    private static native float[] getJNInormals(long scene, int index);
    private static native float[] getJNIcolors(long scene, int index);
    private static native float[] getJNItextureCoords(long scene, int index);
    private static native int[] getJNIindices(long scene, int index);
    private static native String getJNImeshName(long scene, int index);
    private static native int getJNImaterialIndex(long scene, int index);
    private static native int getJNInumAnimeshes(long scene, int index);

    // methods indexed by animesh
    private static native float[] getJNIanimeshVertices(long scene, int meshIndex, int animeshIndex);

    // methods indexed by material
    private static native int getJNIshadingModel(long scene, int index);
    private static native boolean enableJNIwireframe(long scene, int index);
    private static native float[] getJNIambientRGBA(long scene, int index);
    private static native float[] getJNIdiffuseRGBA(long scene, int index);
    private static native float[] getJNIspecularRGBA(long scene, int index);
    private static native float getJNIopacity(long scene, int index);
    private static native float getJNItransparency(long scene, int index);
    private static native float getJNIshininess(long scene, int index);
    private static native float getJNIstrength(long scene, int index);
    private static native boolean getJNIdoubleSided(long scene, int index);
    private static native String getJNImaterialName(long scene, int index);
    private static native String getJNIambientName(long scene, int index);
    private static native String getJNIdiffuseName(long scene, int index);
    private static native String getJNIspecularName(long scene, int index);
    private static native String getJNInormalMapName(long scene, int index);
    private static native boolean hasJNIambientTexture(long scene, int index);
    private static native boolean hasJNIdiffuseTexture(long scene, int index);
    private static native boolean hasJNIspecularTexture(long scene, int index);
    private static native boolean hasJNInormalMap(long scene, int index);

    // methods indexed by light
    private static native int getJNIlightType(long scene, int index);
    private static native float[] getJNIlightDirection(long scene, int index);
    private static native float[] getJNIlightPosition(long scene, int index);
    private static native float[] getJNIlightAmbientRGB(long scene, int index);
    private static native float[] getJNIlightDiffuseRGB(long scene, int index);
    private static native float[] getJNIlightSpecularRGB(long scene, int index);

    // methods indexed by label
    private static native String getJNIembeddedLabel(long scene, String label);
    private static native int getJNIembeddedOffset(long scene, String label);
    private static native int getJNIembeddedLength(long scene,  String label);
    private static native byte[] getJNIembeddedBytes(long scene,  String label);

    // methods indexed by animation
    private static native String getJNIanimationName(long scene, int animation);
    private static native double getJNIanimationDuration(long scene, int animation);
    private static native int getJNInumChannels(long scene, int animation);
    private static native int getJNInumMeshChannels(long scene, int animation);
    private static native int getJNInumMorphMeshChannels(long scene, int animation);
    private static native float[] getJNItranslationKeyframes(long scene, int animation);
    private static native float[] getJNIorientationKeyframes(long scene, int animation);
    private static native float[] getJNIscalingKeyframes(long scene, int animation);
    private static native int getJNInumMorphKeyFrames(long scene, int animation);

    // methods indexed by key
    private static native int[] getJNImorphVertices(long scene, int animation);
    private static native double[] getJNImorphVertexWeights(long scene, int animation);

    public enum aiShadingModel {
        Flat,
        Gouraud,
        Phong,
        Blinn,
        Toon,
        OrenNayar,
        Minnaert ,
        CookTorrance,
        NoShading,
        Fresnel,
    };
}
