package gishleveltool;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;

public class Main {

    public static void main(String[] args) {
        try {
            System.out.println("---");
            System.out.println("FREEGISH JAVA LEVEL TOOL v0.3");
            System.out.println("Please read LICENSE.TXT in the tools/gishleveltool directory");
            System.out.println("Current Directory: " + new File(".").getCanonicalPath());
            System.out.println("---");

            File f = new File("level");
            if (f.exists()) {

                BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
                System.out.println("Decide: ");
                System.out.println("[c] - Format10 -> Format11 conversion + extraction/md5db -- NO BACKUP, DELETES ORIGINAL DATA");
                System.out.println("[x] - Format10 -> Format11 conversion + extraction/md5db -- backup data to _old.lvl");
                System.out.println("[z] - RECOMMENDED: Format10 -> Format11 conversion + extraction/md5db -- backup data to 'backup' directory");
                System.out.println("[u] - Update all selfReference md5DBs");
                System.out.println("### GUI FUNCTIONS ###");
                System.out.println("[m] - Open MD5DB editor");
                System.out.println("#####################");
                System.out.println("[q] - Quit FreeGish Level Conversion");


                while (true) {
                    String option = br.readLine();
                    if (option.equals("q")) {
                        System.exit(0);
                    } else if (option.equals("c")) {
                        Leveltoolkit.format10_to_format11_md5tex(Leveltoolkit.BACKUPS__NO_BACKUPS);
                        System.exit(0);
                    } else if (option.equals("x")) {
                        Leveltoolkit.format10_to_format11_md5tex(Leveltoolkit.BACKUPS__OLD_LVL_BACKUP);
                        System.exit(0);
                    } else if (option.equals("z")) {
                        Leveltoolkit.format10_to_format11_md5tex(Leveltoolkit.BACKUPS__BACKUP_FOLDER_BACKUP);
                        System.exit(0);
                    } else if (option.equals("u")) {
                        Leveltoolkit.update_selfRefs();
                        System.exit(0);
                    } else if (option.equals("m")) {
                        MD5dbmaker mD5dbmaker = new MD5dbmaker();
                        mD5dbmaker.setVisible(true);
                        while (mD5dbmaker != null) {
                        }
                        System.exit(0);
                    } else {
                        System.out.println("**Unknown command: " + option);
                    }
                }

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
}
