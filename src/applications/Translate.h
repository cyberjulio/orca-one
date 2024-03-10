#pragma once

#include <WString.h>
#include <map>
#include <FS.h>

#include "../domain/entities/Language.h"
using namespace Domain::Entities;

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Applications
    {
        class Translate
        {
        private:
            std::map<String, String> _texts;
            Language _language;
            void deserialize(String jsonString);
            static Translate *_instance;
            static bool _initialized;

        public:
            Translate(Language language, String jsonString);

            static Translate *getInstance();

            static Translate *fromFile(Language language, fs::FS &fs, const char *fileName);
            Language getLanguage();
            String get(String key);
        };
    }
#ifdef __cplusplus
}
#endif