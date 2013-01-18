#pragma once

#include <tr1/memory>
#include <vector>

class MatrixBufferInt;

class MatrixBufferFloat {
public:
    MatrixBufferFloat();
    MatrixBufferFloat(int m, int n);
    MatrixBufferFloat(float* data, int m, int n);
    MatrixBufferFloat(double* data, int m, int n);
    ~MatrixBufferFloat() {}

    void AppendVertical(const MatrixBufferFloat& buffer);
    MatrixBufferFloat Transpose() const;
    MatrixBufferFloat Slice(const MatrixBufferInt& indices) const;

    void Zero();
    void SetAll(const float value);

    int GetM() const { return mM; }
    int GetN() const { return mN; }

    void Set(int m, int n, float value);
    float Get(int m, int n) const;
    void SetUnsafe(int m, int n, float value) { (*mData)[m*mN + n] = value; }
    float GetUnsafe(int m, int n) const { return (*mData)[ m*mN + n]; }

    const float* GetRowPtrUnsafe(int m) const { return &(*mData)[m*mN]; }

    float GetMax() const;
    float GetMin() const;
    

    MatrixBufferFloat SharedMemoryCopy() { return *this; }
    void AsNumpy(float* outfloat2d, int m, int n);

private:
    std::tr1::shared_ptr< std::vector< float > > mData;
    int mM;
    int mN;
};


class MatrixBufferInt {
public:
    MatrixBufferInt();
    MatrixBufferInt(int m, int n);
    MatrixBufferInt(int* data, int m, int n);
    MatrixBufferInt(long long* data, int m, int n);
    ~MatrixBufferInt() {}

    void AppendVertical(const MatrixBufferInt& buffer);
    MatrixBufferInt Transpose() const;
    MatrixBufferInt Slice(const MatrixBufferInt& indices) const;

    void SetAll(const int value);
    void Zero();

    int GetM() const { return mM; }
    int GetN() const { return mN; }

    void Set(int m, int n, int value);
    int Get(int m, int n) const;
    void SetUnsafe(int m, int n, int value) { (*mData)[m*mN + n] = value; }
    int GetUnsafe(int m, int n) const { return (*mData)[ m*mN + n]; }

    const int* GetRowPtrUnsafe(int m) const { return &(*mData)[m*mN]; }

    int GetMax() const;
    int GetMin() const;

    MatrixBufferInt SharedMemoryCopy() { return *this; }
    void AsNumpy(int* outint2d, int m, int n);

private:
    std::tr1::shared_ptr< std::vector< int > > mData;
    int mM;
    int mN;
};



MatrixBufferFloat vecBufferFloat(float* float1d, int m);
MatrixBufferFloat vecBufferFloat64(double* double1d, int m);
MatrixBufferInt vecBufferInt(int* int1d, int m);
MatrixBufferInt vecBufferInt64(long long* long1d, int m);

MatrixBufferFloat matrixBufferFloat(float* float2d, int m, int n);
MatrixBufferFloat matrixBufferFloat64(double* double2d, int m, int n);
MatrixBufferInt matrixBufferInt(int* int2d, int m, int n);
MatrixBufferInt matrixBufferInt64(long long* long2d, int m, int n);

