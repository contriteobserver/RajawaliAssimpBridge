package org.rajawali.rajawaliassimpbridge;

public class Bridge {

    // Used to load the bridge library on application startup.
    static {
        System.loadLibrary("bridgeJNI");
    }

    static String getVersion() { return getJNIversion(); }
    static long createImporter() { return createJNIimporter(); }
    static void destroyImporter(long importer) { destroyJNIimporter(importer); }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    private static native String getJNIversion();
    private static native long createJNIimporter();
    private static native void destroyJNIimporter(long importer);

}
