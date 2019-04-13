#ifndef TREKSTAR_DVDSIDE_H
#define TREKSTAR_DVDSIDE_H

#include <map>
#include <string>
#include <vector>

using StringVector = std::vector<std::string>;
using KeyValueMap = std::map<std::string, std::string>;

namespace TrekStar {
    namespace Material {
        class DVDSide {
        protected:
            std::string content;                                // DVD contents
            std::vector<std::string> additionalLanguageTracks;  // other languages available
            std::vector<std::string> additionalSubtitleTracks;  // any additional subtitles
            std::vector<std::string> bonusFeatures;             // for short films or directors comments

        public:
            DVDSide() = default;
            DVDSide(const std::string & content,
                    StringVector additionalLanguageTracks,
                    StringVector additionalSubtitleTracks,
                    StringVector bonusFeatures);

            KeyValueMap GetPresentableInformation() const;
            std::vector<std::string> GetAdditionalLanguageTracks() const;
            std::vector<std::string> GetAdditionalSubtitleTracks() const;
            std::vector<std::string> GetBonusFeatures() const;
        };
    }
}


#endif //TREKSTAR_DVDSIDE_H