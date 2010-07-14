package gishleveltool;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FilenameFilter;
import java.io.IOException;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;

public class Leveltoolkit {

    public static final int BACKUPS__NO_BACKUPS = 0;
    public static final int BACKUPS__OLD_LVL_BACKUP = 1;
    public static final int BACKUPS__BACKUP_FOLDER_BACKUP = 2;

    public static void update_selfRefs() throws IOException {
        File tdir = new File("texture");

        if (tdir.exists()) {
            FileRecursion fr = new FileRecursion(10) {

                public final HashMap<String, MD5db> md5dbs_hmap = new HashMap<String, MD5db>();

                public final HashMap<String, MD5db> getHashMap() {
                    return md5dbs_hmap;
                }

                @Override
                public void fileDetected(File f) {
                    String path = f.getPath().replace("\\", "/");
                    if (path.endsWith(".png")) {
                        try {
                            String relativepath = path;
                            if (relativepath.startsWith("texture/")) {
                                relativepath = relativepath.substring("texture/".length());
                            }
                            int fi = relativepath.indexOf("/");
                            String refFname = "";
                            if (fi != -1) {
                                //non-root dir: texture/.../
                                refFname = relativepath.substring(0, fi);
                            } else {
                                //root dir: texture/
                                refFname = "root";
                            }
                            if (refFname.equals("converted")) {
                            } else {
                                refFname += "_selfref.md5db";

                                System.out.println("FILEZ: " + refFname + " for file " + path + " and relativepath " + relativepath);
                                MD5db working_md5db = md5dbs_hmap.get(refFname);
                                if (working_md5db == null) { //not loaded yet
                                    working_md5db = MD5db.load("texture/md5dbs/" + refFname);
                                    if (working_md5db == null) { //doesn't even exist yet!
                                        working_md5db = new MD5db();
                                    }
                                    md5dbs_hmap.put(refFname, working_md5db);
                                }
                                //loaded!
                                String md5 = Gishlevel.getMD5fromImage(ImageIO.read(f));
                                working_md5db.put(md5, path);
                            }
                        } catch (NoSuchAlgorithmException ex) {
                            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (IOException ex) {
                            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                }
            };
            fr.recurse(tdir);
            for (String md5db_fname : fr.getHashMap().keySet()) {
                fr.getHashMap().get(md5db_fname).save("texture/md5dbs/" + md5db_fname);
            }
        }
    }

    public static void format10_to_format11_md5tex(int backuptype) throws FileNotFoundException, IOException, ClassNotFoundException {
        File f = new File("level");
        if (f.exists()) {
            ArrayList<MD5db> md5dbs = new ArrayList<MD5db>();
            File fmd5 = new File("texture/md5dbs");
            if (!fmd5.exists()) {
                fmd5.mkdir();
            }
            String[] files_md5 = fmd5.list(new FilenameFilter() {

                public boolean accept(File dir, String name) {
                    return (name.endsWith(".md5db"));
                }
            });
            for (String s : files_md5) {
                md5dbs.add(MD5db.load("texture/md5dbs/" + s));
            }




            File fbd = new File("level/backup");
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
                    gishlevel.loadlevel("level/" + s);
                    if (Gishlevel.readCInt(gishlevel.version) == 10) {
                        System.out.println(" Converting: " + s);
                        if (backuptype == BACKUPS__OLD_LVL_BACKUP) {
                            File fbk = new File("level/" + s);
                            fbk.renameTo(new File("level/" + s.replace(".lvl", "_old.lvl")));
                        } else if (backuptype == BACKUPS__BACKUP_FOLDER_BACKUP) {
                            File fbk = new File("level/" + s);
                            fbk.renameTo(new File("level/backup/" + s));
                        }
                        gishlevel.extract_and_convert(md5dbs);
                        gishlevel.savelevel("level/" + s);
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
