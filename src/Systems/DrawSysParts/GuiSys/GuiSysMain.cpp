#include "GuiSys.h"
#include "Models/WindowInfoModel.h"
namespace DrawSys
{
    namespace GuiSys
    {
        void init()
        {
            WindowInfoModel &wim = WindowInfoModel::getInstance();
            // Setup Dear ImGui binding
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            (void)io;
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

            ImGui_ImplGlfw_InitForOpenGL(wim.window, true);
            ImGui_ImplOpenGL3_Init();

            // Setup style
            //ImGui::StyleColorsDark();
            //ImGui::StyleColorsClassic();
            ImGui::StyleColorsLight();

            // Load Fonts
            // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
            // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
            // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
            // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
            // - Read 'misc/fonts/README.txt' for more instructions and details.
            // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
            //io.Fonts->AddFontDefault();
            //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
            //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);

            auto font_default = io.Fonts->AddFontDefault();
            auto font_cousine = io.Fonts->AddFontFromFileTTF("resource/font/Cousine-Regular.ttf", 15.0f);
            auto font_karla = io.Fonts->AddFontFromFileTTF("resource/font/Karla-Regular.ttf", 18.0f);
            auto font_lato = io.Fonts->AddFontFromFileTTF("resource/font/Lato-Regular.ttf", 18.0f);

            io.Fonts->AddFontFromFileTTF("resource/font/DroidSans.ttf", 16.0f);
            io.Fonts->AddFontFromFileTTF("resource/font/ProggyTiny.ttf", 10.0f);
            // ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
            // IM_ASSERT(font != NULL);
        }
    } // namespace GuiSys
} // namespace DrawSys