#include "tglang.h"

#include "resources/third_party/catboost/c_api.h"
#include "resources/third_party/catboost/wrapped_calcer.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <unistd.h>
#include <vector>
#include <sstream>

enum TglangLanguage tglang_detect_programming_language(const char *text) {

  std::vector<std::string> input = {text};

  if (text == nullptr || text[0] == '\0') {
    return TGLANG_LANGUAGE_OTHER;
  }

  // std::cout << text << std::endl;

  std::string modelFilePathBase = "./resources/v1_code_vs_other_depth11_vocab15000.cbm";

  ModelCalcerWrapper calcerBase;
  calcerBase.init_from_file(modelFilePathBase);

  const std::vector<double> predictionsBase = calcerBase.CalcMulti({}, {}, input, {});

  std::cout << "Length of predictions vector: " << predictionsBase.size() << std::endl;

  if (predictionsBase[0] <= 0) {
   	return TGLANG_LANGUAGE_OTHER;
  }

  std::string modelFilePath = "./resources/v1_languages_depth9_vocab5000.cbm";

  ModelCalcerWrapper calcer;
  calcer.init_from_file(modelFilePath);

  const std::vector<double> predictions = calcer.CalcMulti({}, {}, input, {});

  // Initialize variables to keep track of min and max values and their indices
  double maxValue = -std::numeric_limits<double>::max();
  int maxIndex = -1;

  // Loop through the predictions to find min and max values
  for (int i = 0; i < predictions.size(); ++i) {
      double prediction = predictions[i];

      if (prediction > maxValue) {
          maxValue = prediction;
          maxIndex = i;
      }
  }

  // Define the vector of programming languages
  std::vector<enum TglangLanguage> programmingLanguages = {
	TGLANG_LANGUAGE_C, TGLANG_LANGUAGE_CPLUSPLUS, TGLANG_LANGUAGE_CSHARP, TGLANG_LANGUAGE_CSS,
 	TGLANG_LANGUAGE_DART, TGLANG_LANGUAGE_DOCKER, TGLANG_LANGUAGE_FUNC, TGLANG_LANGUAGE_GO,
 	TGLANG_LANGUAGE_HTML, TGLANG_LANGUAGE_JAVA, TGLANG_LANGUAGE_JAVASCRIPT, TGLANG_LANGUAGE_JSON,
 	TGLANG_LANGUAGE_KOTLIN, TGLANG_LANGUAGE_LUA, TGLANG_LANGUAGE_NGINX, TGLANG_LANGUAGE_OBJECTIVE_C,
 	TGLANG_LANGUAGE_PHP, TGLANG_LANGUAGE_POWERSHELL, TGLANG_LANGUAGE_PYTHON, TGLANG_LANGUAGE_RUBY,
 	TGLANG_LANGUAGE_RUST, TGLANG_LANGUAGE_SHELL, TGLANG_LANGUAGE_SOLIDITY, TGLANG_LANGUAGE_SQL,
 	TGLANG_LANGUAGE_SWIFT, TGLANG_LANGUAGE_TL, TGLANG_LANGUAGE_TYPESCRIPT, TGLANG_LANGUAGE_XML
  };

  // Print min and max values and their corresponding indices
  std::cout << "Language: " << programmingLanguages[maxIndex] << std::endl;

  return programmingLanguages[maxIndex];
}
