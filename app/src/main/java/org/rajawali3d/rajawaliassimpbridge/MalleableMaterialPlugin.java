package org.rajawali3d.rajawaliassimpbridge;

import android.opengl.GLES20;

import org.rajawali3d.Geometry3D;
import org.rajawali3d.materials.Material;
import org.rajawali3d.materials.plugins.IMaterialPlugin;
import org.rajawali3d.materials.shaders.AShader;
import org.rajawali3d.materials.shaders.AShaderBase;
import org.rajawali3d.materials.shaders.IShaderFragment;
import org.rajawali3d.math.MathUtil;

import java.nio.DoubleBuffer;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;

public class MalleableMaterialPlugin implements IMaterialPlugin {
    MalleableVertexShaderFragment mVertexShader;

    public enum MalleableShaderVar implements AShaderBase.IGlobalShaderVar {
        U_MORPH_INTERPOLATION("uMorphInterpolation", AShaderBase.DataType.FLOAT),
        A_MORPH_POSITION("aMorphPosition", AShaderBase.DataType.VEC3),
        A_MORPH_NORMAL("aMorphNormal", AShaderBase.DataType.VEC3);

        private String mVarString;
        private AShaderBase.DataType mDataType;

        MalleableShaderVar(String varString, AShaderBase.DataType dataType) {
            mVarString = varString;
            mDataType = dataType;
        }

        public String getVarString() {
            return mVarString;
        }

        public AShaderBase.DataType getDataType() {
            return mDataType;
        }
    }

    public MalleableMaterialPlugin() {
        mVertexShader = new MalleableVertexShaderFragment();
    }

    public void setVertices(float[] vertices) {
        FloatBuffer buffer = FloatBuffer.allocate(vertices.length);
        buffer.put(vertices);
        mVertexShader.setVertices(buffer);
    }

    public void setNormals(float[] normals) {
        FloatBuffer buffer = FloatBuffer.allocate(normals.length);
        buffer.put(normals);
        mVertexShader.setNormals(buffer);
    }

    public void setInterpolation(double interpolation) {
        mVertexShader.setInterpolation((float)interpolation);
    }
    @Override
    public Material.PluginInsertLocation getInsertLocation() {
        return Material.PluginInsertLocation.PRE_TRANSFORM;
    }

    @Override
    public IShaderFragment getVertexShaderFragment() {
        return mVertexShader;
    }

    @Override
    public IShaderFragment getFragmentShaderFragment() {
        return null;
    }

    @Override
    public void bindTextures(int i) {
        mVertexShader.bindTextures(i);
    }

    @Override
    public void unbindTextures() {

    }

    class MalleableVertexShaderFragment extends AShader implements IShaderFragment {
        static final String SHADER_ID = "Malleable_VERTEX_SHADER_FRAGMENT";

        RVec3 maMorphPosition;
        FloatBuffer maMorphPositionBuffer;
        int maMorphPositionBufferHandle;
        int maMorphPositionHandle;

        RVec3 maMorphNormal;
        FloatBuffer maMorphNormalBuffer;
        int maMorphNormalBufferHandle;
        int maMorphNormalHandle;

        RInt maMorphIndices;
        IntBuffer maMorphIndicesBuffer;
        int maMorphIndicesBufferHandle;
        int maMorphIndicesHandle;

        RFloat maMorphWeights;
        DoubleBuffer maMorphWeightsBuffer;
        int maMorphWeightsBufferHandle;
        int maMorphWeightsHandle;
        
        RFloat muInterpolation;
        float mInterpolation = 0;
        int muInterpolationHandle;

        public MalleableVertexShaderFragment() {
            super(ShaderType.VERTEX_SHADER_FRAGMENT);
            initialize();
        }

        @Override
        public String getShaderId() {
            return SHADER_ID;
        }

        public void initialize() {
            super.initialize();
            mInterpolation = 0;
            muInterpolation = (RFloat) addUniform(MalleableShaderVar.U_MORPH_INTERPOLATION);
            maMorphPosition = (RVec3) addAttribute(MalleableShaderVar.A_MORPH_POSITION);
            maMorphNormal = (RVec3) addAttribute(MalleableShaderVar.A_MORPH_NORMAL);
        }

        public void setInterpolation(float interpolation) {

            mInterpolation = (float)MathUtil.clamp(interpolation, 0, 1);
        }

        public void setVertices(FloatBuffer vertices) {
            maMorphPositionBuffer = vertices;
            maMorphPositionBuffer.compact().position(0);
        }

        public void setNormals(FloatBuffer normals) {
            maMorphNormalBuffer = normals;
            maMorphNormalBuffer.compact().position(0);

        }

        public void setIndices(IntBuffer indices) {
            maMorphIndicesBuffer = indices;
            maMorphIndicesBuffer.compact().position(0);
        }

        public void setWeights(DoubleBuffer weights) {
            maMorphWeightsBuffer = weights;
            maMorphWeightsBuffer.compact().position(0);
        }
        
        @Override
        public Material.PluginInsertLocation getInsertLocation() {
            return null;
        }

        @Override
        public void applyParams() {
            super.applyParams();
            GLES20.glUniform1f(muInterpolationHandle, mInterpolation);
        }

        @Override
        public void setLocations(int programHandle) {
            super.setLocations(programHandle);
            muInterpolationHandle = getUniformLocation(programHandle, MalleableShaderVar.U_MORPH_INTERPOLATION);

            int buff[] = new int[2];
            GLES20.glGenBuffers(2, buff, 0);
            maMorphPositionBufferHandle = buff[0];
            maMorphNormalBufferHandle = buff[1];
            status = GLES20.glGetError();

            GLES20.glBindAttribLocation(programHandle, maMorphPositionBufferHandle, MalleableShaderVar.A_MORPH_POSITION.getVarString());
            GLES20.glBindAttribLocation(programHandle, maMorphNormalBufferHandle, MalleableShaderVar.A_MORPH_NORMAL.getVarString());
            status = GLES20.glGetError();

            maMorphPositionHandle = GLES20.glGetAttribLocation(programHandle, MalleableShaderVar.A_MORPH_POSITION.getVarString());
            maMorphNormalHandle = GLES20.glGetAttribLocation(programHandle, MalleableShaderVar.A_MORPH_NORMAL.getVarString());
            status = GLES20.glGetError();
        }

        int status;
        @Override
        public void bindTextures(int i) {
            if(maMorphPositionHandle >= 0) {
                GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, maMorphPositionBufferHandle);
                GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, maMorphPositionBuffer.capacity() * Geometry3D.FLOAT_SIZE_BYTES, maMorphPositionBuffer, GLES20.GL_STATIC_DRAW);
                GLES20.glVertexAttribPointer(maMorphPositionHandle, 3, GLES20.GL_FLOAT, false, 0, 0);
                GLES20.glEnableVertexAttribArray(maMorphPositionHandle);
                status = GLES20.glGetError();
            }

            if(maMorphNormalHandle >= 0) {
                GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, maMorphNormalBufferHandle);
                GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, maMorphNormalBuffer.capacity() * Geometry3D.FLOAT_SIZE_BYTES, maMorphNormalBuffer, GLES20.GL_STATIC_DRAW);
                GLES20.glVertexAttribPointer(maMorphNormalHandle, 3, GLES20.GL_FLOAT, false, 0, 0);
                GLES20.glEnableVertexAttribArray(maMorphNormalHandle);
                status = GLES20.glGetError();
            }
        }

        @Override
        public void unbindTextures() {

        }

        @Override
        public void main() {
            RVec4 position = (RVec4)getGlobal(DefaultShaderVar.G_POSITION);
            RVec3 normal = (RVec3)getGlobal(DefaultShaderVar.G_NORMAL);
            RVec4 aPosition = (RVec4)getGlobal(DefaultShaderVar.A_POSITION);
            RVec3 aNormal = (RVec3)getGlobal(DefaultShaderVar.A_NORMAL);

            position.assign(mix(aPosition, castVec4(maMorphPosition, 1), muInterpolation));
            normal.assign(mix(aNormal, maMorphNormal, muInterpolation));
            normalize(normal);
        }
    }
}

