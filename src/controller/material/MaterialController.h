#ifndef SDI_PROJECT_MATERIALCONTROLLER_H
#define SDI_PROJECT_MATERIALCONTROLLER_H

#include <memory>

#include "../../model/material/Material.h"
#include "../../view/material/MaterialView.h"
#include "../../model/material/MaterialInterface.h"
#include "../BaseController.h"

namespace TrekStar
{
    namespace Material
    {
        class MaterialController : public BaseController
        {
        private:
            MaterialInterface* model;
            ViewInterface* view;

            MaterialView* GetView();

            void UpdateAudioFormat();
            void UpdateRunTime();
            void UpdateLanguage();
            void UpdateRetailPrice();
            void UpdateSubtitles();
            void UpdateFrameAspect();
            void UpdatePackaging();

        public:
            MaterialController() = default;
            MaterialController(MaterialInterface & model, ViewInterface & view);
            ~MaterialController() = default;

            void ShowAll() override;
            void ShowList() override;

            void Update();
        };
    }
}

#endif //SDI_PROJECT_MATERIALCONTROLLER_H
