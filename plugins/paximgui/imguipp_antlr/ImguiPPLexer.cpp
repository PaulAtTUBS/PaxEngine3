
// Generated from ImguiPPLexer.g4 by ANTLR 4.10.1


#include "ImguiPPLexer.h"


using namespace antlr4;

using namespace Antlr;


using namespace antlr4;

namespace {

struct ImguiPPLexerStaticData final {
  ImguiPPLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ImguiPPLexerStaticData(const ImguiPPLexerStaticData&) = delete;
  ImguiPPLexerStaticData(ImguiPPLexerStaticData&&) = delete;
  ImguiPPLexerStaticData& operator=(const ImguiPPLexerStaticData&) = delete;
  ImguiPPLexerStaticData& operator=(ImguiPPLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag imguipplexerLexerOnceFlag;
ImguiPPLexerStaticData *imguipplexerLexerStaticData = nullptr;

void imguipplexerLexerInitialize() {
  assert(imguipplexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<ImguiPPLexerStaticData>(
    std::vector<std::string>{
      "WS", "SINGLELINE_COMMENT", "MULTILINE_COMMENT", "LINEBREAK", "IMGUI", 
      "IMGUI_RANGED", "ANYTHING_ELSE", "BRACKET_L", "BRACKET_R", "IDENTIFIER", 
      "COMMA", "EQUALS", "SEMICOLON", "UNIFORM_INITIAL_VALUE", "UNIFORM_INITIALIZATION_END"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE", "IMGUI_ANNOTATION_MODE", "UNIFORM_INITIALIZATION"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "'IMGUI_RANGED'", "", "'('", "')'", "", "','", 
      "'='"
    },
    std::vector<std::string>{
      "", "WS", "SINGLELINE_COMMENT", "MULTILINE_COMMENT", "LINEBREAK", 
      "IMGUI", "IMGUI_RANGED", "ANYTHING_ELSE", "BRACKET_L", "BRACKET_R", 
      "IDENTIFIER", "COMMA", "EQUALS", "SEMICOLON", "UNIFORM_INITIAL_VALUE", 
      "UNIFORM_INITIALIZATION_END"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,15,147,6,-1,6,-1,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,
  	7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,
  	7,13,2,14,7,14,1,0,4,0,35,8,0,11,0,12,0,36,1,0,1,0,1,1,5,1,42,8,1,10,
  	1,12,1,45,9,1,1,1,1,1,1,1,1,1,5,1,51,8,1,10,1,12,1,54,9,1,1,1,1,1,1,2,
  	5,2,59,8,2,10,2,12,2,62,9,2,1,2,1,2,1,2,1,2,1,2,5,2,69,8,2,10,2,12,2,
  	72,9,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,
  	4,5,4,90,8,4,10,4,12,4,93,9,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,4,6,113,8,6,11,6,12,6,114,1,6,1,6,1,7,
  	1,7,1,8,1,8,1,9,4,9,124,8,9,11,9,12,9,125,1,10,1,10,1,11,1,11,1,11,1,
  	11,1,12,1,12,1,12,1,12,1,13,4,13,139,8,13,11,13,12,13,140,1,14,1,14,1,
  	14,1,14,1,14,2,70,114,0,15,3,1,5,2,7,3,9,4,11,5,13,6,15,7,17,8,19,9,21,
  	10,23,11,25,12,27,13,29,14,31,15,3,0,1,2,5,2,0,9,9,32,32,3,0,9,10,13,
  	13,32,32,2,0,10,10,13,13,6,0,9,9,32,32,40,41,44,44,59,59,61,61,1,0,59,
  	59,154,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,
  	13,1,0,0,0,0,15,1,0,0,0,1,17,1,0,0,0,1,19,1,0,0,0,1,21,1,0,0,0,1,23,1,
  	0,0,0,1,25,1,0,0,0,1,27,1,0,0,0,2,29,1,0,0,0,2,31,1,0,0,0,3,34,1,0,0,
  	0,5,43,1,0,0,0,7,60,1,0,0,0,9,78,1,0,0,0,11,82,1,0,0,0,13,96,1,0,0,0,
  	15,112,1,0,0,0,17,118,1,0,0,0,19,120,1,0,0,0,21,123,1,0,0,0,23,127,1,
  	0,0,0,25,129,1,0,0,0,27,133,1,0,0,0,29,138,1,0,0,0,31,142,1,0,0,0,33,
  	35,7,0,0,0,34,33,1,0,0,0,35,36,1,0,0,0,36,34,1,0,0,0,36,37,1,0,0,0,37,
  	38,1,0,0,0,38,39,6,0,0,0,39,4,1,0,0,0,40,42,7,1,0,0,41,40,1,0,0,0,42,
  	45,1,0,0,0,43,41,1,0,0,0,43,44,1,0,0,0,44,46,1,0,0,0,45,43,1,0,0,0,46,
  	47,5,47,0,0,47,48,5,47,0,0,48,52,1,0,0,0,49,51,8,2,0,0,50,49,1,0,0,0,
  	51,54,1,0,0,0,52,50,1,0,0,0,52,53,1,0,0,0,53,55,1,0,0,0,54,52,1,0,0,0,
  	55,56,6,1,0,0,56,6,1,0,0,0,57,59,7,1,0,0,58,57,1,0,0,0,59,62,1,0,0,0,
  	60,58,1,0,0,0,60,61,1,0,0,0,61,63,1,0,0,0,62,60,1,0,0,0,63,64,5,47,0,
  	0,64,65,5,42,0,0,65,70,1,0,0,0,66,69,7,1,0,0,67,69,9,0,0,0,68,66,1,0,
  	0,0,68,67,1,0,0,0,69,72,1,0,0,0,70,71,1,0,0,0,70,68,1,0,0,0,71,73,1,0,
  	0,0,72,70,1,0,0,0,73,74,5,42,0,0,74,75,5,47,0,0,75,76,1,0,0,0,76,77,6,
  	2,0,0,77,8,1,0,0,0,78,79,7,2,0,0,79,80,1,0,0,0,80,81,6,3,0,0,81,10,1,
  	0,0,0,82,83,5,73,0,0,83,84,5,77,0,0,84,85,5,71,0,0,85,86,5,85,0,0,86,
  	87,5,73,0,0,87,91,1,0,0,0,88,90,3,3,0,0,89,88,1,0,0,0,90,93,1,0,0,0,91,
  	89,1,0,0,0,91,92,1,0,0,0,92,94,1,0,0,0,93,91,1,0,0,0,94,95,6,4,1,0,95,
  	12,1,0,0,0,96,97,5,73,0,0,97,98,5,77,0,0,98,99,5,71,0,0,99,100,5,85,0,
  	0,100,101,5,73,0,0,101,102,5,95,0,0,102,103,5,82,0,0,103,104,5,65,0,0,
  	104,105,5,78,0,0,105,106,5,71,0,0,106,107,5,69,0,0,107,108,5,68,0,0,108,
  	109,1,0,0,0,109,110,6,5,1,0,110,14,1,0,0,0,111,113,9,0,0,0,112,111,1,
  	0,0,0,113,114,1,0,0,0,114,115,1,0,0,0,114,112,1,0,0,0,115,116,1,0,0,0,
  	116,117,6,6,0,0,117,16,1,0,0,0,118,119,5,40,0,0,119,18,1,0,0,0,120,121,
  	5,41,0,0,121,20,1,0,0,0,122,124,8,3,0,0,123,122,1,0,0,0,124,125,1,0,0,
  	0,125,123,1,0,0,0,125,126,1,0,0,0,126,22,1,0,0,0,127,128,5,44,0,0,128,
  	24,1,0,0,0,129,130,5,61,0,0,130,131,1,0,0,0,131,132,6,11,2,0,132,26,1,
  	0,0,0,133,134,5,59,0,0,134,135,1,0,0,0,135,136,6,12,3,0,136,28,1,0,0,
  	0,137,139,8,4,0,0,138,137,1,0,0,0,139,140,1,0,0,0,140,138,1,0,0,0,140,
  	141,1,0,0,0,141,30,1,0,0,0,142,143,5,59,0,0,143,144,1,0,0,0,144,145,6,
  	14,3,0,145,146,6,14,3,0,146,32,1,0,0,0,13,0,1,2,36,43,52,60,68,70,91,
  	114,125,140,4,6,0,0,5,1,0,5,2,0,4,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  imguipplexerLexerStaticData = staticData.release();
}

}

ImguiPPLexer::ImguiPPLexer(CharStream *input) : Lexer(input) {
  ImguiPPLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *imguipplexerLexerStaticData->atn, imguipplexerLexerStaticData->decisionToDFA, imguipplexerLexerStaticData->sharedContextCache);
}

ImguiPPLexer::~ImguiPPLexer() {
  delete _interpreter;
}

std::string ImguiPPLexer::getGrammarFileName() const {
  return "ImguiPPLexer.g4";
}

const std::vector<std::string>& ImguiPPLexer::getRuleNames() const {
  return imguipplexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& ImguiPPLexer::getChannelNames() const {
  return imguipplexerLexerStaticData->channelNames;
}

const std::vector<std::string>& ImguiPPLexer::getModeNames() const {
  return imguipplexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& ImguiPPLexer::getVocabulary() const {
  return imguipplexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ImguiPPLexer::getSerializedATN() const {
  return imguipplexerLexerStaticData->serializedATN;
}

const atn::ATN& ImguiPPLexer::getATN() const {
  return *imguipplexerLexerStaticData->atn;
}




void ImguiPPLexer::initialize() {
  std::call_once(imguipplexerLexerOnceFlag, imguipplexerLexerInitialize);
}
