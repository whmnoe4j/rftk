%module pipeline
%{
    #define SWIG_FILE_WITH_INIT
    #include "BufferTypes.h"
    #include "UniqueBufferId.h"
    #include "PipelineStepI.h"
    #include "Pipeline.h"
    #include "AllSamplesStep.h"
    #include "BootstrapSamplesStep.h"
    #include "PoissonSamplesStep.h"
    #include "PoissonStep.h"
    #include "SetBufferStep.h"
    #include "SliceBufferStep.h"
    #include "FeatureInfoLoggerI.h"
    #include "FeatureExtractorStep.h"
    #include "FeatureEqualI.h"
    #include "FeatureEqualQuantized.h"
    #include "FeatureRangeStep.h"

    #if PY_VERSION_HEX >= 0x03020000
    # define SWIGPY_SLICE_ARG(obj) ((PyObject*) (obj))
    #else
    # define SWIGPY_SLICE_ARG(obj) ((PySliceObject*) (obj))
    #endif
%}

%include <exception.i>
%import(module="rftk.utils") "utils.i"
%import(module="rftk.buffers") "buffers.i"
%include <pipeline_external.i>

%include "std_vector.i"

namespace std {
    %template(PipelineVector) std::vector<PipelineStepI*>;
}

%include "UniqueBufferId.h"
%include "PipelineStepI.h"
%include "Pipeline.h"
%include "AllSamplesStep.h"
%include "BootstrapSamplesStep.h"
%include "PoissonSamplesStep.h"
%include "PoissonStep.h"
%include "SetBufferStep.h"
%include "SliceBufferStep.h"
%include "FeatureInfoLoggerI.h"
%include "FeatureExtractorStep.h"
%include "FeatureEqualI.h"
%include "FeatureEqualQuantized.h"
%include "FeatureRangeStep.h"

%template(AllSamplesStep_f32f32i32) AllSamplesStep< DefaultBufferTypes, MatrixBufferTemplate<DefaultBufferTypes::SourceContinuous> >;
%template(AllSamplesStep_i32f32i32) AllSamplesStep< DefaultBufferTypes, MatrixBufferTemplate<DefaultBufferTypes::SourceInteger> >;
%template(BootstrapSamplesStep_f32f32i32) BootstrapSamplesStep< DefaultBufferTypes, MatrixBufferTemplate<DefaultBufferTypes::SourceContinuous> >;
%template(BootstrapSamplesStep_i32f32i32) BootstrapSamplesStep< DefaultBufferTypes, MatrixBufferTemplate<DefaultBufferTypes::SourceInteger> >;
%template(PoissonSamplesStep_f32i32) PoissonSamplesStep< DefaultBufferTypes, MatrixBufferTemplate<DefaultBufferTypes::SourceContinuous> >;
%template(PoissonSamplesStep_i32i32) PoissonSamplesStep< DefaultBufferTypes, MatrixBufferTemplate<DefaultBufferTypes::SourceInteger> >;

%template(AllSamplesStep_Sparse_f32f32i32) AllSamplesStep< DefaultBufferTypes, SparseMatrixBufferTemplate<DefaultBufferTypes::SourceContinuous> >;
%template(AllSamplesStep_Sparse_i32f32i32) AllSamplesStep< DefaultBufferTypes, SparseMatrixBufferTemplate<DefaultBufferTypes::SourceInteger> >;
%template(BootstrapSamplesStep_Sparse_f32f32i32) BootstrapSamplesStep< DefaultBufferTypes, SparseMatrixBufferTemplate<DefaultBufferTypes::SourceContinuous> >;
%template(BootstrapSamplesStep_Sparse_i32f32i32) BootstrapSamplesStep< DefaultBufferTypes, SparseMatrixBufferTemplate<DefaultBufferTypes::SourceInteger> >;
%template(PoissonSamplesStep_Sparse_f32i32) PoissonSamplesStep< DefaultBufferTypes, SparseMatrixBufferTemplate<DefaultBufferTypes::SourceContinuous> >;
%template(PoissonSamplesStep_Sparse_i32i32) PoissonSamplesStep< DefaultBufferTypes, SparseMatrixBufferTemplate<DefaultBufferTypes::SourceInteger> >;

%template(PoissonStep_f32i32) PoissonStep< DefaultBufferTypes >;


%template(SetContinuousVectorBufferStep) SetBufferStep< VectorBufferTemplate<DefaultBufferTypes::SourceContinuous> >;
%template(SetIntegerVectorBufferStep) SetBufferStep< VectorBufferTemplate<DefaultBufferTypes::SourceInteger> >;
%template(SetContinuousMatrixBufferStep) SetBufferStep< MatrixBufferTemplate<DefaultBufferTypes::SourceContinuous> >;
%template(SetIntegerMatrixBufferStep) SetBufferStep< MatrixBufferTemplate<DefaultBufferTypes::SourceInteger> >;

%template(SetFloat32VectorBufferStep) SetBufferStep< VectorBufferTemplate<float> >;
%template(SetFloat64VectorBufferStep) SetBufferStep< VectorBufferTemplate<double> >;
%template(SetInt32VectorBufferStep) SetBufferStep< VectorBufferTemplate<int> >;
%template(SetInt64VectorBufferStep) SetBufferStep< VectorBufferTemplate<long long> >;

%template(SetFloat32MatrixBufferStep) SetBufferStep< MatrixBufferTemplate<float> >;
%template(SetFloat64MatrixBufferStep) SetBufferStep< MatrixBufferTemplate<double> >;
%template(SetInt32MatrixBufferStep) SetBufferStep< MatrixBufferTemplate<int> >;
%template(SetInt64MatrixBufferStep) SetBufferStep< MatrixBufferTemplate<long long> >;

%template(SliceFloat32MatrixBufferStep_i32) SliceBufferStep< DefaultBufferTypes, MatrixBufferTemplate<DefaultBufferTypes::SourceContinuous> >;
%template(SliceFloat32VectorBufferStep_i32) SliceBufferStep< DefaultBufferTypes, VectorBufferTemplate<DefaultBufferTypes::SourceContinuous> >;
%template(SliceInt32VectorBufferStep_i32) SliceBufferStep< DefaultBufferTypes, VectorBufferTemplate<DefaultBufferTypes::SourceInteger> >;

%template(FeatureEqualI_f32i32) FeatureEqualI< DefaultBufferTypes >;
%template(FeatureEqualQuantized_f32i32) FeatureEqualQuantized< DefaultBufferTypes >;

%template(FeatureRangeStep_Default) FeatureRangeStep< DefaultBufferTypes >;