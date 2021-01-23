package org.rajawali.rajawaliassimpbridge;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.util.Log;
import android.view.MotionEvent;
import android.widget.TextView;

import org.rajawali3d.Object3D;
import org.rajawali3d.animation.Animation;
import org.rajawali3d.animation.Animation3D;
import org.rajawali3d.animation.RotateOnAxisAnimation;
import org.rajawali3d.lights.DirectionalLight;
import org.rajawali3d.materials.Material;
import org.rajawali3d.math.vector.Vector3;
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
            getCurrentScene().setBackgroundColor(Color.MAGENTA & Color.DKGRAY);

            Log.i(getLocalClassName() + ".version", Bridge.getVersion());
            scene = Bridge.readFile(importer, "tetrahedron.fbx");
            Log.i(getLocalClassName() + ".initScene", "parsed " + Bridge.getNumMeshes(scene)+ " meshes");

            Object3D obj = new Object3D();
            getCurrentScene().addChild(obj);

            if(scene==0) {
                Log.e(getLocalClassName() + ".readFile", Bridge.errorMessage(scene));
            } else {
                for(int i=0; i<Bridge.getNumMeshes(scene); i++) {
                    Material material = Bridge.getMaterialAt(scene, Bridge.getMaterialIndex(scene, i));
                    Object3D child = Bridge.getObjAt(scene, i);
                    child.setMaterial(material);
                    obj.addChild(child);
                }
                Bridge.freeScene(importer);
            }

            Animation3D anim = new RotateOnAxisAnimation(Vector3.Axis.Y, 360);
            anim.setTransformable3D(obj);
            anim.setDurationDelta(6);
            anim.setRepeatMode(Animation.RepeatMode.INFINITE);
            anim.play();
            getCurrentScene().registerAnimation(anim);

            getCurrentCamera().setPosition(5,3,-4);
            getCurrentCamera().setLookAt(Vector3.ZERO);
        }

        @Override
        public void onOffsetsChanged(float xOffset, float yOffset, float xOffsetStep, float yOffsetStep, int xPixelOffset, int yPixelOffset) {

        }

        @Override
        public void onTouchEvent(MotionEvent event) {

        }
    }
}