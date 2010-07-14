package gishleveltool;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;

public class FileRecursion {

    private int maxRecursions;

    public FileRecursion(int maxRecursions) {
        this.maxRecursions = maxRecursions;
    }

    public void recurse(File file) throws IOException {
        recurse(file, 1);
    }

    public void recurse(File file, int recursion) throws IOException {
        if (recursion < maxRecursions) {
            if (file.isDirectory()) {
                directoryDetected(file);
                File[] nodes = file.listFiles();
                for (File n : nodes) {
                    recurse(n);
                }
                return;
            } else {
                fileDetected(file);
            }
        }
    }

    public void directoryDetected(File f) {
        System.out.println("Directory: " + f.getPath());
    }

    public void fileDetected(File f) {
        System.out.println("File: " + f.getPath());
    }

    public HashMap<String, MD5db> getHashMap() {
        return null; //unimplemented, function for updateDBs
    }
}
