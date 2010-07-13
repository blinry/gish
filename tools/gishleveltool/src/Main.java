/*
 * Gish level loader and possible converter thingy
 */
package gishleveltool;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FilenameFilter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Main {

    public static final int BACKUPS__NO_BACKUPS = 0;
    public static final int BACKUPS__OLD_LVL_BACKUP = 1;
    public static final int BACKUPS__BACKUP_FOLDER_BACKUP = 2;



    public static void main(String[] args) {
        try {
            System.out.println("---");
            System.out.println("FREEGISH JAVA LEVEL TOOL v0.2");
            System.out.println("Current Directory: " + new File(".").getCanonicalPath());
            System.out.println("---");

            File f = new File("level");
            if (f.exists()) {
                BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
                System.out.println("Decide: ");
                System.out.println("[c] - Convert all format10 levels to format11 levels with md5 reference textures -- NO BACKUP, DELETES ORIGINAL DATA");
                System.out.println("[x] - Convert all format10 levels to format11 levels with md5 reference textures -- backup data to _old.lvl");
                System.out.println("[z] - RECOMMENDED: Convert all format10 levels to format11 levels with md5 reference textures -- backup data to 'backup' directory");
                System.out.println("[q] - Quit FreeGish Level Conversion");


                while (true) {
                    String option = br.readLine();
                    if (option.equals("q")) {
                        System.exit(0);
                    } else if (option.equals("c")) {
                        format10_to_format11_md5tex(BACKUPS__NO_BACKUPS);
                        System.exit(0);
                    } else if (option.equals("x")) {
                        format10_to_format11_md5tex(BACKUPS__OLD_LVL_BACKUP);
                        System.exit(0);
                    } else if (option.equals("z")) {
                        format10_to_format11_md5tex(BACKUPS__BACKUP_FOLDER_BACKUP);
                        System.exit(0);
                    } else {
                        System.out.println("**Unknown command: " + option);
                    }
                }
//        Gishlevel g1 = new Gishlevel();
//        Gishlevel g2 = new Gishlevel();
//        /*g1.loadlevel("D:\\git_repos\\gish\\level\\gish.lvl"); //load level 1
//        g2.loadlevel("D:\\git_repos\\gish\\level\\sewer4.lvl"); //loadlevel 2
//        g2.tiles = g1.tiles; //transfer textures and block definitions
//        g2.level_tileset = g1.level_tileset; //transfer 'tileset' (not really needed)
//        g2.version = g1.version; //transfer version (don't forget this! :P)
//        g2.savelevel("D:\\git_repos\\gish\\level\\sewer4b.lvl"); //save level! Woo. It's now converted!*/
//
//
//
//        Gishlevel g4 = new Gishlevel();
//        g4.loadlevel("level\\sewer1.lvl");
//        if (Gishlevel.readCInt(g4.version) == 10) {
//            System.out.println("Converting!");
//            System.out.println("Converting!");
//            System.out.println("Converting!");
//            System.out.println("Converting!");
//            System.out.println("Converting!");
//
//                    System.out.println("Converting!");
//            System.out.println("Converting!");
//            g4.extract_and_convert();
//        }
//        g4.savelevel("level\\sewer1.lvl");
//
//
//        System.err.println("DONE");
//        System.err.println("DONE");
//        System.err.println("DONE");
//        System.err.println("DONE");
//        System.err.println("DONE");
//        System.err.println("DONE");
//        System.err.println("DONE");
//
//        Gishlevel g3 = new Gishlevel();
//        g3.loadlevel("c:\\gragh.lvl");

            } else {
                System.out.println("ERROR: directory 'level' does not exist! Are you running this from the correct path!?");
                System.out.println("-NOW EXITING-");
                System.exit(1);
            }

        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    public static void format10_to_format11_md5tex(int backuptype) throws FileNotFoundException {
        File f = new File("level");
        if (f.exists()) {
            File fbd = new File("level\\backup");
            if (!fbd.exists()) {
                fbd.mkdir();
            }
            String[] files = f.list(new FilenameFilter() {

                public boolean accept(File dir, String name) {
                    if (name.endsWith(".lvl")) {
                        return true;
                    }
                    return false;
                }
            });
            for (String s : files) {
                try {
                    System.out.println("Loading: " + s);
                    Gishlevel gishlevel = new Gishlevel();
                    gishlevel.loadlevel("level\\" + s);
                    if (Gishlevel.readCInt(gishlevel.version) == 10) {
                        System.out.println(" Converting: " + s);
                        if (backuptype == BACKUPS__OLD_LVL_BACKUP) {
                            File fbk = new File("level\\" + s);
                            fbk.renameTo(new File("level\\" + s.replace(".lvl", "_old.lvl")));
                        } else if (backuptype == BACKUPS__BACKUP_FOLDER_BACKUP) {
                            File fbk = new File("level\\" + s);
                            fbk.renameTo(new File("level\\backup\\" + s));
                        }
                        gishlevel.extract_and_convert();
                        gishlevel.savelevel("level\\" + s);
                    } else {
                        System.out.println(" Not converting " + s + " -- level version is " + Gishlevel.readCInt(gishlevel.version));
                    }
                } catch (IOException ex) {
                    Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        } else {
            System.out.println("ERROR: directory 'level' does not exist! Are you running this from the correct path!?");
        }
    }
}
