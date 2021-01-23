package org.rajawali.rajawaliassimpbridge;

import android.content.res.AssetManager;
import android.graphics.Color;

import org.rajawali3d.Object3D;
import org.rajawali3d.materials.Material;
import org.rajawali3d.materials.methods.DiffuseMethod;
import org.rajawali3d.materials.methods.SpecularMethod;

public class Bridge {

    // Used to load the bridge library on application startup.
    static {
        System.loadLibrary("bridgeJNI");
    }

    static String getVersion() { return getJNIversion(); }
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

        Material material = new Material();
        material.setColor(getJNIdiffuseRGBA(scene, index));
        material.setColorInfluence(getJNIopacity(scene, index));
        material.setAmbientColor(getJNIambientRGBA(scene, index));
        material.setDiffuseMethod(new DiffuseMethod.Lambert());
        material.setSpecularMethod(new SpecularMethod.Phong(specularColor, shininess, intensity));
        material.enableLighting(true);
        return material;
    }

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

    // methods indexed by material
    private static native float[] getJNIambientRGBA(long scene, int index);
    private static native float[] getJNIdiffuseRGBA(long scene, int index);
    private static native float[] getJNIspecularRGBA(long scene, int index);
    private static native float getJNIopacity(long scene, int index);
    private static native float getJNIshininess(long scene, int index);
    private static native float getJNIstrength(long scene, int index);
    private static native boolean getJNIdoubleSided(long scene, int index);
}
