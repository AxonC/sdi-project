#include "pch.h"
#include "DVDSide.h"

namespace TrekStar
{
    namespace Material
    {
        DVDSide::DVDSide(const std::string & content, StringVector additionalLanguageTracks, StringVector additionalSubtitleTracks, StringVector bonusFeatures)
        {
            this->content = content;
            this->additionalLanguageTracks = additionalLanguageTracks;
            this->additionalSubtitleTracks = additionalSubtitleTracks;
            this->bonusFeatures = bonusFeatures;
        }

        std::string DVDSide::GetContent() const
        {
            return content;
        };

        std::vector<std::string> DVDSide::GetAdditionalLanguageTracks() const
        {
            return this->additionalLanguageTracks;
        }

        std::vector<std::string> DVDSide::GetAdditionalSubtitleTracks() const
        {
            return this->additionalSubtitleTracks;
        }

        std::vector<std::string> DVDSide::GetBonusFeatures() const
        {
            return this->bonusFeatures;
        }

        KeyValueMap DVDSide::GetPresentableInformation() const
        {
            KeyValueMap information;

            information.insert(std::pair<std::string, std::string>("Content", this->content));

            int counter = 0;
            for ( auto & it: this->additionalLanguageTracks )
            {
                counter++;
                information.insert(std::pair<std::string, std::string>("Additional Language Track " + std::to_string(counter), it));
            }

            counter = 0;
            for ( auto & it: this->additionalSubtitleTracks )
            {
                counter++;
                information.insert(std::pair<std::string, std::string>("Additional Subtitle Track " + std::to_string(counter), it));
            }

            counter = 0;
            for ( auto & it: this->bonusFeatures )
            {
                counter++;
                information.insert(std::pair<std::string, std::string>("Bonus Features " + std::to_string(counter), it));
            }

            return information;
        }

        void DVDSide::SetContent(const std::string & content)
        {
            this->content = content;
        }

        void DVDSide::SetAdditionalLanguageTracks(const std::vector<std::string> & additionalLanguageTracks)
        {
            this->additionalLanguageTracks = additionalLanguageTracks;
        }

        void DVDSide::SetAdditionalSubtitleTracks(const std::vector<std::string> & additionalSubtitleTracks)
        {
            this->additionalSubtitleTracks = additionalSubtitleTracks;
        }

        void DVDSide::SetBonusFeatures(const std::vector<std::string> & bonusFeatures)
        {
            this->bonusFeatures = bonusFeatures;
        }

        void DVDSide::SetAdditionalLanguageTrack(unsigned int index, const std::string & languageTrack)
        {
            if ( index >= this->additionalLanguageTracks.size() )
            {
                this->additionalLanguageTracks.resize(index + 1);
            }

            this->additionalLanguageTracks.at(index) = languageTrack;
        }

        void DVDSide::SetAdditionalSubtitleTrack(unsigned int index, const std::string & subtitleTrack)
        {
            if ( index >= this->additionalSubtitleTracks.size() )
            {
                this->additionalSubtitleTracks.resize(index + 1);
            }

            this->additionalSubtitleTracks.at(index) = subtitleTrack;
        }

        void DVDSide::SetBonusFeature(unsigned int index, const std::string & bonusFeature)
        {
            if ( index >= this->bonusFeatures.size() )
            {
                this->bonusFeatures.resize(index + 1);
            }

            this->bonusFeatures.at(index) = bonusFeature;
        }

        SerialisedDVDSide DVDSide::ExportToSerialised() const
        {
            return SerialisedDVDSide
                {
                    this->content,
                    this->additionalLanguageTracks,
                    this->additionalSubtitleTracks,
                    this->bonusFeatures
                };
        }
    }
}
