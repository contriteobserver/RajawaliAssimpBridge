package org.rajawali.rajawaliassimpbridge;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;

import org.rajawali3d.Object3D;
import org.rajawali3d.animation.Animation;
import org.rajawali3d.animation.Animation3D;
import org.rajawali3d.animation.AnimationGroup;
import org.rajawali3d.animation.RotateOnAxisAnimation;
import org.rajawali3d.lights.ALight;
import org.rajawali3d.lights.DirectionalLight;
import org.rajawali3d.materials.Material;
import org.rajawali3d.math.Quaternion;
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

        Log.i(getLocalClassName() + ".version", Bridge.getVersion());
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
            try {
                getCurrentScene().setBackgroundColor(Color.MAGENTA & Color.DKGRAY);

                Object3D obj = new Object3D();
                getCurrentScene().addChild(obj);

                scene = Bridge.readFile(importer, "tetrahedron01.gltf");
                if(scene==0) {
                    Log.e(getLocalClassName() + ".readFile", Bridge.errorMessage(importer));
                } else {
                    Log.i(getLocalClassName() + ".initScene", "parsed " + Bridge.getNumLights(scene)+ " lights");
                    for(int i=0; i<Bridge.getNumLights(scene); i++) {
                        ALight light = Bridge.getLightAt(scene, i);
                        getCurrentScene().addLight(light);
                    }
                    if(Bridge.getNumLights(scene)==0) {
                        DirectionalLight key = new DirectionalLight(-5,-5,-5);
                        key.setPower(5/4f);
                        getCurrentScene().addLight(key);
                    }

                    Log.i(getLocalClassName() + ".initScene", "parsed " + Bridge.getNumMeshes(scene)+ " meshes");
                    for(int i=0; i<Bridge.getNumMeshes(scene); i++) {
                        Material material = Bridge.getMaterialAt(scene, Bridge.getMaterialIndex(scene, i));
                        if(Bridge.hasDiffuseTexture(scene, Bridge.getMaterialIndex(scene, i))) {
                            AssimpTexture texture = new AssimpTexture(getAssets());
                            texture.loadDiffuseData(scene, Bridge.getMaterialIndex(scene, i));
                            material.addTexture(texture);
                        }
                        if(Bridge.hasNormalMap(scene, Bridge.getMaterialIndex(scene, i))) {
                            AssimpTexture texture = new AssimpTexture(getAssets());
                            texture.loadNormalMap(scene, Bridge.getMaterialIndex(scene, i));
                            material.addTexture(texture);
                        }
                        Object3D child = Bridge.getObjAt(scene, i);
                        child.setMaterial(material);
                        obj.addChild(child);
                    }

                    Log.i(getLocalClassName() + ".initScene", "parsed " + Bridge.getNumAnimations(scene)+ " animations");
                    for(int i=0; i<Bridge.getNumAnimations(scene); i++) {
                        AnimationGroup anim = Bridge.getAnimationFor(obj, scene, i);
                        anim.play();
                        getCurrentScene().registerAnimation(anim);
                    }
                    if(Bridge.getNumAnimations(scene)==0) {
                        Animation3D anim = new RotateOnAxisAnimation(Vector3.Axis.Y, 360);
                        anim.setTransformable3D(obj);
                        anim.setDurationDelta(9);
                        anim.setRepeatMode(Animation.RepeatMode.INFINITE);
                        anim.play();
                        getCurrentScene().registerAnimation(anim);
                    }

                    Bridge.freeScene(importer);
                }

                getCurrentCamera().setPosition(5,3,-4);
                getCurrentCamera().setLookAt(Vector3.ZERO);
            } catch(Exception e) {
                Log.e(getLocalClassName(), e.getMessage());
            }
        }

        @Override
        public void onOffsetsChanged(float xOffset, float yOffset, float xOffsetStep, float yOffsetStep, int xPixelOffset, int yPixelOffset) {

        }

        @Override
        public void onTouchEvent(MotionEvent event) {

        }
    }
}