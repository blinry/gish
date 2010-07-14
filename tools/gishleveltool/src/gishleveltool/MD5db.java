package gishleveltool;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.TreeMap;
import java.util.Set;
import javax.imageio.ImageIO;
import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name = "MD5DB")
public class MD5db {

    ArrayList<String> comments;
    private TreeMap<String, String> md5Map;

    public MD5db() {
        md5Map = new TreeMap<String, String>();
        comments = new ArrayList<String>();
    }

    public void put(String md5, String toFile) {
        md5Map.put(md5, toFile);
    }

    public String getFile(String md5) {
        return md5Map.get(md5);
    }

    public void save(String path) throws FileNotFoundException, IOException {
        FileWriter fw = new FileWriter(new File(path));
        for (String s : comments) {
            fw.write(s + "\n");
        }
        for (String s : md5Map.keySet()) {
            fw.write(s + "\n");
            fw.write(md5Map.get(s) + "\n");
        }
        fw.close();
    }

    public static MD5db load(String path) throws IOException {
        BufferedReader br;
        try {
            br = new BufferedReader(new FileReader(new File(path)));
        } catch (FileNotFoundException ex) {
            //Logger.getLogger(MD5db.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
        MD5db ret = new MD5db();
        ArrayList<String> llist = new ArrayList<String>();
        while (br.ready()) {
            String parse = br.readLine();
            if (parse.startsWith("#")) {
                ret.comments.add(parse);
            } else {
                llist.add(parse);
            }
            while (llist.size() >= 2) {
                ret.put(llist.get(0), llist.get(1));
                llist.remove(0);
                llist.remove(0);
            }
        }
        return ret;
    }

    public void generate(String directory) throws IOException, NoSuchAlgorithmException {
        File f = new File(directory);
        String[] files = f.list();
        for (String s : files) {
            String md5 = Gishlevel.getMD5fromImage(ImageIO.read(new File(directory + "/" + s)));
            put(md5, s);
            System.out.println("MD5DB: added " + md5 + " toFile " + s);
        }
    }

    public Set<String> getEntries() {
        return md5Map.keySet();
    }
}
