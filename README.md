📒 Notes Maker

A simple, clean, and lightweight note-taking application built using Qt 6 and C++.
The app allows users to create, view, edit, and delete notes with automatic saving to a local file (notes.dat).

🚀 Features
✔ Minimal & Fast

No database setup required — everything is stored locally.

Lightweight UI using Qt Widgets.

✔ Create Notes

Write notes using a built-in text editor.

Title is automatically generated from the first 30 characters.

✔ View / Edit Notes

Click any note from the list to instantly load and edit it.

✔ Delete Notes

Remove unwanted notes from the list and storage.

✔ Auto-Save System

All notes automatically save to notes.dat using QDataStream.

🛠️ Tech Stack

C++

Qt 6 (Qt Widgets)

QMainWindow / QListWidget / QTextEdit

QDataStream for file serialization

📂 Project Structure
NotesMaker/
 ├── main.cpp
 ├── notes.dat            # Generated automatically after first run
 ├── CMakeLists.txt       # or .pro file depending on your build system
 ├── resources/
 └── README.md

📦 How to Build
Qt Creator

Open main.cpp or your .pro / CMakeLists.txt file in Qt Creator.

Configure the project for your Qt 6 kit.

Press Build → Run.

CMake (Command Line)
mkdir build
cd build
cmake ..
cmake --build .

💾 File Storage Behavior

The app saves notes in a binary file named:

notes.dat


Each entry is stored as:

Key: Note Title (QString)
Value: Note Content (QString)


You do not need to manually create this file — it is generated automatically.

🪄 How It Works (Core Logic)
Load Notes on Startup
loadNotes();

Save Notes on Exit
QObject::connect(mainWindow, &QMainWindow::destroyed, saveNotes);

Save Note

Uses the first 30 characters as the title

Saves entire content to the map

Delete Note

Removes note from notes map

Updates UI and clears editor

🖼 UI Overview
Left Panel

List of all notes

New Note button

Delete Note button

Right Panel

Large text editor

Save Note button

🔮 Future Improvements (Optional Ideas)

Search notes

Custom note titles

Dark mode

Markdown rendering

Export notes to .txt

📜 License

This project has an MIT License attached to it.
