#include "ImguiInterface.h"

void ImguiInterface::draw_interface()
{
    ImguiInterface::draw_mainwindow();
}

bool ImguiInterface::b_mainwindow = true;
void ImguiInterface::draw_mainwindow()
{
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        if (b_mainwindow)
        {
            ImGui::Begin("Some panel", &b_mainwindow);
            ImGui::Text("Hello World");
            ImGui::End();
        }
        ImGui::ShowDemoWindow(&b_mainwindow);
        ImGui::EndFrame();
}
