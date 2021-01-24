package org.rajawali.rajawaliassimpbridge;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import org.rajawali3d.materials.textures.ASingleTexture;

import java.io.IOException;
import java.io.InputStream;

class AssimpTexture extends ASingleTexture {
    AssetManager mAssetManager;

    public AssimpTexture(AssetManager assetManager)
    {
        super();
        mAssetManager = assetManager;
    }

    public AssimpTexture(ASingleTexture other) {
        super(other);
    }

    String getTextureName(String assetName) {
        return assetName.substring(0, assetName.indexOf("."));
    }

    public void loadDiffuseData(long scene, int i) throws IOException {
        mTextureType = TextureType.DIFFUSE;
        String assetName = Bridge.getDiffuseName(scene, i);
        loadData(scene, assetName);
        setInfluence(Bridge.getOpacity(scene,i));
    }

    void loadData(long scene, String assetName) throws IOException {
        if(assetName.startsWith("*")) {
            mTextureName = Bridge.getEmbeddedLabel(scene,assetName);
            int offset = Bridge.getEmbeddedOffset(scene, assetName);
            int length = Bridge.getEmbeddedLength(scene, assetName);
            byte[] data = Bridge.getEmbeddedBytes(scene, assetName);
            setBitmap(BitmapFactory.decodeByteArray(data, offset, length));
        } else {
            mTextureName = getTextureName(assetName);
            InputStream istr = mAssetManager.open(assetName);
            setBitmap(BitmapFactory.decodeStream(istr));
        }
    }

    @Override
    public ASingleTexture clone() { return new AssimpTexture(this); }

}
