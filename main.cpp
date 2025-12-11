#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>

// Global variables
QMainWindow *mainWindow;
QListWidget *notesList;
QTextEdit *noteEditor;
QPushButton *saveButton;
QPushButton *deleteButton;
QMap<QString, QString> notes;  // Key: Note title, Value: Note content

// Function declarations
void setupUI();
void saveNotes();
void loadNotes();
void updateNotesList();
void saveCurrentNote();
void deleteSelectedNote();
void onNoteSelected(QListWidgetItem *item);

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Initialize UI
    setupUI();
    loadNotes();

    mainWindow->show();
    return app.exec();
}

void setupUI() {
    mainWindow = new QMainWindow;
    mainWindow->setWindowTitle("Notes Maker");
    mainWindow->resize(800, 600);

    QWidget *centralWidget = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Left panel (Notes list)
    QWidget *leftPanel = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

    notesList = new QListWidget;
    QObject::connect(notesList, &QListWidget::itemClicked, onNoteSelected);
    leftLayout->addWidget(notesList);

    QPushButton *newButton = new QPushButton("New Note");
    QObject::connect(newButton, &QPushButton::clicked, []() {
        noteEditor->clear();
        notesList->clearSelection();
    });
    leftLayout->addWidget(newButton);

    deleteButton = new QPushButton("Delete Note");
    QObject::connect(deleteButton, &QPushButton::clicked, deleteSelectedNote);
    leftLayout->addWidget(deleteButton);

    // Right panel (Note editor)
    QWidget *rightPanel = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

    noteEditor = new QTextEdit;
    noteEditor->setPlaceholderText("Write your note here...");
    rightLayout->addWidget(noteEditor);

    saveButton = new QPushButton("Save Note");
    QObject::connect(saveButton, &QPushButton::clicked, saveCurrentNote);
    rightLayout->addWidget(saveButton);

    // Add panels to main layout
    mainLayout->addWidget(leftPanel, 1);
    mainLayout->addWidget(rightPanel, 2);

    centralWidget->setLayout(mainLayout);
    mainWindow->setCentralWidget(centralWidget);

    // Save notes when closing
    QObject::connect(mainWindow, &QMainWindow::destroyed, saveNotes);
}

void loadNotes() {
    QFile file("notes.dat");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> notes;
        file.close();
    }
    updateNotesList();
}

void saveNotes() {
    QFile file("notes.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << notes;
        file.close();
    }
}

void updateNotesList() {
    notesList->clear();
    for (const QString &title : notes.keys()) {
        notesList->addItem(title);
    }
}

void saveCurrentNote() {
    QString noteTitle = noteEditor->toPlainText().left(30).trimmed();  // Use first 30 chars as title
    if (noteTitle.isEmpty()) {
        QMessageBox::warning(mainWindow, "Error", "Note cannot be empty!");
        return;
    }

    notes[noteTitle] = noteEditor->toPlainText();
    saveNotes();
    updateNotesList();
}

void deleteSelectedNote() {
    QListWidgetItem *selectedItem = notesList->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(mainWindow, "Error", "No note selected!");
        return;
    }

    QString title = selectedItem->text();
    notes.remove(title);
    saveNotes();
    updateNotesList();
    noteEditor->clear();
}

void onNoteSelected(QListWidgetItem *item) {
    QString title = item->text();
    noteEditor->setText(notes[title]);
}
