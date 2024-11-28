# File Organizer

Move files into appropriate folders according to their extensions (eg: *.jpeg into `Images`).

Use `make` or the task in the .vscode to build the project, then `build/file_organizer <folder path>`.

Try with `build/file_organizer test_directory` and reset the tests file with `make clean`.

```bash
$ build/file_organizer test_directory
test_directory/document.txt --> test_directory/Documents/document.txt
test_directory/video.mp4 --> test_directory/Videos/video.mp4
test_directory/music.mp3 --> test_directory/Music/music.mp3
test_directory/archive.zip --> test_directory/Archives/archive.zip
test_directory/image.jpg --> test_directory/Images/image.jpg
Files organized successfully!
```

Also handles duplicate file names

```bash
$ build/file_organizer test_directory
test_directory/music.mp3 --> test_directory/Music/music(1).mp3
Files organized successfully!
```
