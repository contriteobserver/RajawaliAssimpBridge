package org.rajawali3d.rajawaliassimpbridge;

import org.rajawali3d.Object3D;
import org.rajawali3d.animation.Animation3D;

public class SplineWeightAnimation3D extends Animation3D {

    double mTempPoint1;
    ICurve1D mSplinePath;

    public SplineWeightAnimation3D(ICurve1D splinePath) {
        super();

        mSplinePath = splinePath;
        mTempPoint1 = 0;
    }

    @Override
    protected void applyTransformation() {
        mTempPoint1 = mSplinePath.calculateValue(mInterpolatedTime);
        Object3D obj = (Object3D) mTransformable3D;
        if(obj==null) return;
        MalleableMaterialPlugin plugin = (MalleableMaterialPlugin) obj.getMaterial().getPlugin(MalleableMaterialPlugin.class);
        if(plugin==null) return;
        plugin.setInterpolation(mTempPoint1);
    }

    public void setDurationMilliseconds(long duration) {
        super.setDurationMilliseconds(duration);
    }

}