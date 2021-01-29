package org.rajawali.rajawaliassimpbridge;

import org.rajawali3d.curves.ICurve3D;
import org.rajawali3d.math.vector.Vector3;

import java.util.Collections;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public class Path3D implements ICurve3D {

    protected List<Vector3> mPoints;
    protected int mNumPoints;
    protected boolean mIsClosed;

    public Path3D() {
        mPoints = Collections.synchronizedList(new CopyOnWriteArrayList<Vector3>());
    }

    public void addPoint(Vector3 point) {
        mPoints.add(point);
        mNumPoints++;
    }

    public int getNumPoints()
    {
        return mNumPoints;
    }

    public List<Vector3> getPoints()
    {
        return mPoints;
    }

    public Vector3 getPoint(int index) {
        return mPoints.get(index);
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }

    // mix performs a linear interpolation between x and y using a to weight between them.
    // The return value is computed as x×(1−a)+y×a.
    private Vector3 mix(Vector3 x, Vector3 y, double a) {
        return x.clone().multiply(1-a).add(y.clone().multiply(a));
    }

    @Override
    public void calculatePoint(Vector3 result, double t) {
        while(t < 0) t+=1;
        while(t > 1) t-=1;

        int prev = (int)Math.floor(t*getNumPoints());
        int next = prev+1;
        double tween = (prev-t*getNumPoints());
        if(next < getNumPoints()) {
            result.setAll(mix(getPoint(next), getPoint(prev), tween));
        } else {
            if(mIsClosed) {
                result.setAll(mix(getPoint(0), getPoint(getNumPoints()-1), tween));
            } else {
                result.setAll(getPoint(getNumPoints()-1));
            }
        }
    }

    @Override
    public Vector3 getCurrentTangent() {
        return null;
    }

    @Override
    public void setCalculateTangents(boolean calculateTangents) {

    }

    public void isClosedCurve(boolean closed)
    {
        mIsClosed = closed;
    }

    public boolean isClosedCurve()
    {
        return mIsClosed;
    }

}
