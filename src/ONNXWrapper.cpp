// Minimal ONNX Runtime wrapper stub.
// Compiles only if ENABLE_ONNX_RUNTIME is defined by CMake and onnxruntime is available.
#ifdef ENABLE_ONNX_RUNTIME
#include <onnxruntime_cxx_api.h>
#include <vector>
#include <string>
#include <iostream>

bool run_onnx_inference(const std::string &model_path, const std::vector<float> &input, std::vector<float> &output) {
    try {
        Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "pet");
        Ort::SessionOptions session_options;
        session_options.SetIntraOpNumThreads(1);
        Ort::Session session(env, model_path.c_str(), session_options);
        // NOTE: full example would map inputs/outputs; this is just a placeholder.
        (void)input;
        (void)output;
        std::cout << \"ONNX model loaded: \" << model_path << std::endl;
        return true;
    } catch (const std::exception &e) {
        std::cerr << \"ONNX inference error: \" << e.what() << std::endl;
        return false;
    }
}
#endif