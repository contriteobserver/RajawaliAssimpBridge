package org.rajawali.rajawaliassimpbridge;

import android.content.res.AssetManager;

import org.rajawali3d.Object3D;

public class Bridge {

    // Used to load the bridge library on application startup.
    static {
        System.loadLibrary("bridgeJNI");
    }

    static String getVersion() { return getJNIversion(); }
    static long createImporter(AssetManager assetManager) { return createJNIimporter(assetManager); }
    static long readFile(long importer, String path) { return readJNIfile(importer, path); }
    static long getNumMeshes(long scene) { return getNumJNImeshes(scene); }
    static long getNumMaterials(long scene) { return getNumJNImaterials(scene); }
    static long getNumTextures(long scene) { return getNumJNItextures(scene); }
    static long getNumLights(long scene) { return getNumJNIlights(scene); }
    static long getNumCameras(long scene) { return getNumJNIcameras(scene); }
    static long getNumAnimations(long scene) { return getNumJNIanimations(scene); }
    static void destroyImporter(long importer) { destroyJNIimporter(importer); }

    static Object3D getObjAt(long scene, int i) {
        float[] vertices = getJNIvertices(scene, i);
        float[] normals  = getJNInormals(scene, i);;
        float[] colors  = getJNIcolors(scene, i);;
        float[] textureCoords  = getJNItextureCoords(scene, i);;
        int[] indices  = getJNIindices(scene, i);;

        Object3D obj = new Object3D();
        obj.setData(vertices, normals, textureCoords, colors, indices, true);
        return obj;
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    private static native String getJNIversion();
    private static native long createJNIimporter(AssetManager assetManager);
    private static native long readJNIfile(long importer, String path);
    private static native void destroyJNIimporter(long importer);

    private static native long getNumJNImeshes(long scene);
    private static native long getNumJNImaterials(long scene);
    private static native long getNumJNItextures(long scene);
    private static native long getNumJNIlights(long scene);
    private static native long getNumJNIcameras(long scene);
    private static native long getNumJNIanimations(long scene);

    private static native float[] getJNIvertices(long scene, int mesh);
    private static native float[] getJNInormals(long scene, int mesh);
    private static native float[] getJNIcolors(long scene, int mesh);
    private static native float[] getJNItextureCoords(long scene, int mesh);
    private static native int[] getJNIindices(long scene, int mesh);


}
