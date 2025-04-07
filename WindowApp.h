#pragma once
#include <vector>
#include "Console.h"
#include <conio.h>
#include <iostream>

class WindowApp
{
private:
    Console console;
    std::vector<std::string> tasks;
    int position = 0;

public:
    void showWindow()
    {
        WindowConsole mainWin(&console, 2, 5, 15, 50);
        mainWin.Title() = "Task Manager";
        mainWin.SetColors(Color::Blue, Color::White, Color::Blue, Color::White);
        mainWin.Show();

        for (int i = 0; i < tasks.size(); i++)
        {
            std::string task = (i == position) ? "> " + tasks[i] : "  " + tasks[i];
            mainWin.WriteGoto(i + 2, 3, task);
        }
        mainWin.WriteGoto(12, 3, "Add: A | Delete: D | Move: Up/Down | Exit: Esc");

        if (tasks.empty())
            mainWin.WriteGoto(5, 3, "No tasks. Press 'A' to add.");
    }

    void run()
    {
        console.WriteGoto(0, 0, "Loading...");

        tasks.push_back("Task1");
        tasks.push_back("Task2");
        tasks.push_back("Task3");

        bool running = true;
        while (running) {
            showWindow();

            int key = _getch();
            if (key == 0 || key == 0xE0) key = _getch();

            switch (key)
            {
            case 72:
                if (position > 0)
                    position--;
                break;
            case 80:
                if (!tasks.empty() && position < tasks.size() - 1)
                    position++;
                break;
            case 'a':
            case 'A':
            {
                WindowConsole inputWin(&console, 8, 10, 5, 40);
                inputWin.Title() = "New Task";
                inputWin.SetColors(Color::Green, Color::White, Color::Green, Color::White);
                inputWin.Show();

                std::string newTask;
                console.CursorGoto(10, 12);
                std::cout << "Enter task: ";
                std::getline(std::cin, newTask);

                if (!newTask.empty())
                {
                    tasks.push_back(newTask);
                    position = tasks.size() - 1;
                }
                break;
            }
            case 'd':
            case 'D':
                if (!tasks.empty())
                {
                    tasks.erase(tasks.begin() + position);
                }
                break;
            case 27:
                running = false;
                break;

            }
        }
    }
};