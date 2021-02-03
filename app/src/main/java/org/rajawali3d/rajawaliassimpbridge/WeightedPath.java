package org.rajawali3d.rajawaliassimpbridge;

public class WeightedPath implements ICurve1D {
    double [] weights;
    protected boolean mIsClosed;

    public WeightedPath(double [] weights) {
        this.weights = weights;
    }

    @Override
    public double calculateValue(double t) {
        while(t < 0) t+=1;
        while(t > 1) t-=1;

        int prev = (int)Math.floor(t*weights.length);
        int next = prev+1;
        double tween = t*weights.length-prev;
        if(next < weights.length) {
            return mix(weights[prev], weights[next], tween);
        } else {
            if(mIsClosed) {
                return mix(weights[weights.length-1], weights[0],  tween);
            } else {
                return weights[weights.length-1];
            }
        }
    }

    // mix performs a linear interpolation between x and y using a to weight between them.
    // The return value is computed as x×(1−a)+y×a.
    private double mix(double x, double y, double a) {
        return (x * (1 - a) + y * a);
    }
}
