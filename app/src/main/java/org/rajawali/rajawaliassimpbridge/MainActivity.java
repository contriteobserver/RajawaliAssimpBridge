package org.rajawali.rajawaliassimpbridge;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.util.Log;
import android.view.MotionEvent;
import android.widget.TextView;

import org.rajawali3d.renderer.Renderer;
import org.rajawali3d.view.SurfaceView;

public class MainActivity extends AppCompatActivity {
    SurfaceView view;
    long importer;
    long scene;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.i(getLocalClassName(), Bridge.getVersion());

        ImportRenderer renderer = new ImportRenderer(this);
        view = findViewById(R.id.glsl_content);
        view.setSurfaceRenderer(renderer);

        importer = Bridge.createImporter(getAssets());
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Bridge.destroyImporter(importer);
    }

    class ImportRenderer extends Renderer {

        public ImportRenderer(Context context) {
            super(context);
        }

        @Override
        protected void initScene() {
            scene = Bridge.readFile(importer, "tetrahedron.obj");
            Log.i(getLocalClassName() + ".initScene", "scene = " + scene);
            getCurrentScene().setBackgroundColor(Color.CYAN & Color.DKGRAY);
        }

        @Override
        public void onOffsetsChanged(float xOffset, float yOffset, float xOffsetStep, float yOffsetStep, int xPixelOffset, int yPixelOffset) {

        }

        @Override
        public void onTouchEvent(MotionEvent event) {

        }
    }
}