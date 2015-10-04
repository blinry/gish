package gishleveltool;

import java.awt.image.BufferedImage;
import java.awt.image.RenderedImage;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.EOFException;
import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.ArrayList;
import javax.imageio.ImageIO;

public class Gishlevel {

    static int BITYPE = BufferedImage.TYPE_4BYTE_ABGR;
    byte[] version = new byte[4];
    byte[] level_background = new byte[32];
    byte[] level_tileset = new byte[4];
    byte[] level_gametype = new byte[4];
    byte[] level_time = new byte[4];
    byte[][] level_area = new byte[256][4];
    byte[][] level_backgrid = new byte[256 * 256][1];
    byte[][] level_grid = new byte[256 * 256][1];
    byte[][] level_foregrid = new byte[256 * 256][1];
    byte[][] level_startposition = new byte[3][4];
    byte[][] level_ambient = new byte[12][4];
    byte[] level_numofobjects = new byte[4];
    byte[] objects_data;// = new byte[(4 + 4 + 4 + (4 * 3) + 4 + (4 * 2) + 4 + 4 + 4 + (4 * 3) + 4 + 4) * (int) readCInt(level_numofobjects)];
    byte[] level_numofropes = new byte[4];
    byte[] ropes_data;// = new byte[(4 + 4 + 4 + 4 + 4 + 4) * readCInt(level_numofropes)];
    byte[] block_friction = new byte[4];
    byte[] block_breakpoint = new byte[4];
    byte[] block_middamage = new byte[4];
    byte[] block_foredamage = new byte[4];
    byte[] block_density = new byte[4];
    byte[] block_drag = new byte[4];
    byte[] block_animation = new byte[4];
    byte[] block_animationspeed = new byte[4];
    //ArrayList<byte[]> textures_and_blocks = new ArrayList<byte[]>();
    ArrayList<Tile> tiles = new ArrayList<Tile>();

    public void loadlevel(String path) throws FileNotFoundException {
        File f = new File(path);
        FileInputStream fs = new FileInputStream(f);
        try {
            processFile(fs);
            fs.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

//    public void addtextureblock(byte[] in1, byte[] in2) {
//        byte[] block = cat(in1, in2);
//        addtextureblock(block);
//    }
//
//    public void addtextureblock(byte[] in1) {
//        textures_and_blocks.add(in1);
//    }
    public static Byte[] btoB(byte[] b1) {
        Byte[] b2 = new Byte[b1.length];
        for (int i = 0; i < b1.length; i++) {
            b2[i] = b1[i];
        }
        return b2;
    }

    public static byte[] Btob(Byte[] b1) {
        byte[] b2 = new byte[b1.length];
        for (int i = 0; i < b1.length; i++) {
            b2[i] = b1[i];
        }
        return b2;
    }

    public static byte[] cat(byte[] in1, byte[] in2) {
        byte[] ret = new byte[in1.length + in2.length];
        int count = 0;
        for (int i = 0; i < in1.length; i++) {
            ret[count] = in1[i];
            count++;
        }
        for (int i = 0; i < in2.length; i++) {
            ret[count] = in2[i];
            count++;
        }
        return ret;
    }

    public void processFile(FileInputStream fs) throws IOException, NoSuchAlgorithmException {

        ArrayList<RenderedImage> images = new ArrayList<RenderedImage>();

        /*
        fread2(level.background,1,32,fp);
        fread2(&level.tileset,4,1,fp);
        fread2(&level.gametype,4,1,fp);
        fread2(&level.time,4,1,fp);
        fread2(level.area,4,64*4,fp);
         */

        fs.read(version);
        int offset, read;

        for (offset = 0; offset < level_background.length; offset += read) {
            read = fs.read(level_background, offset, level_background.length - offset);
            if (read < 0) throw new EOFException("Failed to read level background");
        }

        // Need to use trim() here otherwise length() always returns 32.
        String fns = new String(level_background).trim();

        if (fns.endsWith(".tga")) {
            Arrays.fill(level_background, fns.length() - 4, level_background.length, (byte) 0);
        }

        fs.read(level_tileset);
        fs.read(level_gametype);
        fs.read(level_time);
        for (int i = 0; i < level_area.length; i++) {
            int j = fs.read(level_area[i]);
            //System.out.println("Read bytes for " + i + ": " + j);
        }


        /*
        fread2(level.backgrid,1,256*256,fp);
        fread2(level.grid,1,256*256,fp);
        fread2(level.foregrid,1,256*256,fp);
         * */

        for (int i = 0; i < level_backgrid.length; i++) {
            int j = fs.read(level_backgrid[i]);
            //System.out.println("Read bytes for " + i + ": " + j);
        }
        for (int i = 0; i < level_grid.length; i++) {
            int j = fs.read(level_grid[i]);
            //System.out.println("Read bytes for " + i + ": " + j);
        }
        for (int i = 0; i < level_foregrid.length; i++) {
            int j = fs.read(level_foregrid[i]);
            //System.out.println("Read bytes for " + i + ": " + j);
        }

        /*
        fread2(level.startposition,4,3,fp);
        fread2(level.ambient,4,12,fp);
        fread2(&level.numofobjects,4,1,fp);
         */

        for (int i = 0; i < level_startposition.length; i++) {
            int j = fs.read(level_startposition[i]);
            //System.out.println("Read bytes for " + i + ": " + j);
        }
        for (int i = 0; i < level_ambient.length; i++) {
            int j = fs.read(level_ambient[i]);
            //System.out.println("Read bytes for " + i + ": " + j);
        }
        fs.read(level_numofobjects);

        /*
         *OBJECT:
        fread2(&level.object[count].type,4,1,fp);
        fread2(&level.object[count].texturenum,4,1,fp);
        fread2(&level.object[count].link,4,1,fp);
        fread2(level.object[count].position,4,3,fp);
        fread2(&level.object[count].angle,4,1,fp);
        fread2(level.object[count].size,4,2,fp);
        fread2(&level.object[count].mass,4,1,fp);
        fread2(&level.object[count].friction,4,1,fp);
        fread2(&level.object[count].lighttype,4,1,fp);
        fread2(level.object[count].lightcolor,4,3,fp);
        fread2(&level.object[count].lightintensity,4,1,fp);
        fread2(&level.object[count].ai,4,1,fp);
         */

        objects_data = new byte[(4 + 4 + 4 + (4 * 3) + 4 + (4 * 2) + 4 + 4 + 4 + (4 * 3) + 4 + 4) * (int) readCInt(level_numofobjects)];
        fs.read(objects_data);

        /*
        fread2(&level.numofropes,4,1,fp);
         */

        fs.read(level_numofropes);

        /*
         * ROPE:
        fread2(&level.rope[count].type,4,1,fp);
        fread2(&level.rope[count].texturenum,4,1,fp);
        fread2(&level.rope[count].obj1,4,1,fp);
        fread2(&level.rope[count].obj1part,4,1,fp);
        fread2(&level.rope[count].obj2,4,1,fp);
        fread2(&level.rope[count].obj2part,4,1,fp);
         */

        ropes_data = new byte[(4 + 4 + 4 + 4 + 4 + 4) * readCInt(level_numofropes)];
        fs.read(ropes_data);

        for (int i = 1; i < 251; i++) {
            Tile tile = new Tile();
            //TEXTURE
            byte[] sizex = new byte[4];
            fs.read(sizex);
            //addtextureblock(sizex);
            tile.put("sizex", sizex);
            if (readCInt(sizex) < 0) {
                /*
                fread2(filename, 1, filenameLength, fp);
                 */
                int filenamelength = Math.abs(readCInt(sizex));
                //System.out.println(" Filenamelength for tex" + i + ":" + filenamelength);
                if (filenamelength > 256) {
                    System.err.println("ULP! filenamelength:" + filenamelength);
                    filenamelength = 256;
                }
                byte[] filename = new byte[filenamelength];
                fs.read(filename);
                String fname = new String(filename);
                //System.out.println("Tex" + i + " -- REFERENCE -- " + fname);
                tile.put("filename", filename);
                //addtextureblock(filename);




            } else if (readCInt(sizex) == 0) {
                //System.out.println("Tex" + i + " -- BLOB (EMPTY) ");
            } else {
                /* fread2(&texture[count].sizey,4,1,fp);
                fread2(&texture[count].magfilter,4,1,fp);
                fread2(&texture[count].minfilter,4,1,fp);
                free(texture[count].rgba[0]);
                texture[count].rgba[0]=(unsigned int *) malloc(texture[count].sizex*texture[count].sizey*4);
                fread(texture[count].rgba[0],4,texture[count].sizex*texture[count].sizey,fp);*/
                byte[] sizey = new byte[4];
                byte[] magfilter = new byte[4];
                byte[] minfilter = new byte[4];
                fs.read(sizey);
                fs.read(magfilter);
                fs.read(minfilter);
                //addtextureblock(sizey);
                //addtextureblock(magfilter);
                //addtextureblock(minfilter);
                tile.put("sizey", sizey);
                tile.put("magfilter", magfilter);
                tile.put("minfilter", minfilter);
                int sx = readCInt(sizex);
                int sy = readCInt(sizey);


                byte[][] textureblob = new byte[sx * sy][4];
                //System.out.println(" Textureblob size for tex" + i + ":" + textureblob.length);
                int temp_tbsize = sx * sy * 4;
                byte[] textureblob_single = new byte[temp_tbsize];
                for (int ti = 0; ti < textureblob.length; ti++) {
                    fs.read(textureblob[ti]);
                }


                for (int ia = 0; ia < textureblob.length; ia++) {
                    for (int ib = 0; ib < 4; ib++) {
                        textureblob_single[(ia * 4) + ib] = textureblob[ia][ib];
                    }
                }

                tile.put("textureblob", textureblob_single);
                //System.out.println("Tex" + i + " -- BLOB -- sizex:" + readCInt(sizex) + " sizey:" + readCInt(sizey) + " magfilter:" + readCInt(magfilter) + " minfilter:" + readCInt(minfilter));
            }
            //END TEXTURE
            //BLOCK
            /*
            fread2(&block[count].numoflines,4,1,fp);
             */
            byte[] block_numoflines = new byte[4];
            fs.read(block_numoflines);
            //addtextureblock(block_numoflines);
            tile.put("block_numoflines", block_numoflines);
            //System.out.println("Numoflines for tex" + i + ": " + readCInt(block_numoflines));
            //if (readCInt(block_numoflines) >= 0) {

            byte[] block_lines = new byte[8 * 4 * readCInt(block_numoflines)];
            fs.read(block_lines);
            tile.put("block_lines", block_lines);
            //addtextureblock(block_lines); //FOOSH

//            for (int li = 0; li < readCInt(block_numoflines); li++) {
//            byte[][] block_line = new byte[8][4];
//
//            int temp_bsize = 8 * 4;
//            byte[] block_lines = new byte[temp_bsize];
//
//            for (int lli = 0; lli < block_line.length; lli++) {
//            fs.read(block_line[lli]);
//            addtextureblock(block_line[lli]); //FOOSH
//            block_lines = cat(block_lines, block_line[lli]);
//            }
//
//            tile.put("block_lines", block_lines);
//            }
            //}
            /*
            fread2(&block[count].friction,4,1,fp);
            fread2(&block[count].breakpoint,4,1,fp);
            fread2(&block[count].middamage,4,1,fp);
            fread2(&block[count].foredamage,4,1,fp);
            fread2(&block[count].density,4,1,fp);
            fread2(&block[count].drag,4,1,fp);
            fread2(&block[count].animation,4,1,fp);
            fread2(&block[count].animationspeed,4,1,fp);
             */



            block_friction = new byte[4];
            block_breakpoint = new byte[4];
            block_middamage = new byte[4];
            block_foredamage = new byte[4];
            block_density = new byte[4];
            block_drag = new byte[4];
            block_animation = new byte[4];
            block_animationspeed = new byte[4];

            fs.read(block_friction);
            tile.put("block_friction", block_friction);
            //addtextureblock(block_friction);
            fs.read(block_breakpoint);
            tile.put("block_breakpoint", block_breakpoint);
            //addtextureblock(block_breakpoint);
            fs.read(block_middamage);
            tile.put("block_middamage", block_middamage);
            //addtextureblock(block_middamage);
            fs.read(block_foredamage);
            tile.put("block_foredamage", block_foredamage);
            //addtextureblock(block_foredamage);
            fs.read(block_density);
            tile.put("block_density", block_density);
            //addtextureblock(block_density);
            fs.read(block_drag);
            tile.put("block_drag", block_drag);
            //addtextureblock(block_drag);
            fs.read(block_animation);
            tile.put("block_animation", block_animation);
            //addtextureblock(block_animation);
            fs.read(block_animationspeed);
            tile.put("block_animationspeed", block_animationspeed);
            //addtextureblock(block_animationspeed);

            //END BLOCK
            tiles.add(tile);
            //System.out.println("Tile size in bytes: " + tile.getTileData().length);
        }

        //System.out.println("---READING DONE---");

        System.out.println("Version: " + readCInt(version));
        /*System.out.println(
        "Level tileset: " + readCInt(level_tileset));
        System.out.println(
        "Level gametype: " + readCInt(level_gametype));
        System.out.println(
        "Level time (?WRONG?): " + readCInt(level_time));
        System.out.println(
        "Level start position (?): " + readCInt(level_startposition[0]) + "," + readCInt(level_startposition[1]) + "," + readCInt(level_startposition[2]));
         */

        /*for (int i = 0;
        i < level_ambient.length;
        i++) {
        System.out.println("Level_ambient[" + i + "]: " + readCFloat(level_ambient[i]));
        }*/

        //System.out.println("Num of objects: " + readCInt(level_numofobjects));
        /*System.out.println(
        "(Size of objects data: " + objects_data.length + " bytes)");
         */
        //System.out.println(
        //        "Num of ropes: " + readCInt(level_numofropes));
        /*System.out.println(
        "(Size of ropes data: " + ropes_data.length + " bytes)");
        System.out.println("num of tiles: " + tiles.size());
         */

        /*for (int y = 0; y < 256; y++) {
        String out = "";
        for (int x = 0; x < 256; x++) {
        out += level_foregrid[(y * 256) + x][0];
        }
        System.out.println(out);
        }

        System.gc();
        drawMap(level_foregrid);*/

    }

    public void savelevel(String path) {
        try {
            FileOutputStream fos = new FileOutputStream(new File(path));

            fos.write(version);
            fos.write(level_background);
            fos.write(level_tileset);
            fos.write(level_gametype);
            fos.write(level_time);
            write_dbarray(level_area, fos);
            write_dbarray(level_backgrid, fos);
            write_dbarray(level_grid, fos);
            write_dbarray(level_foregrid, fos);
            write_dbarray(level_startposition, fos);
            write_dbarray(level_ambient, fos);
            fos.write(level_numofobjects);
            fos.write(objects_data);
            fos.write(level_numofropes);
            fos.write(ropes_data);
            for (Tile t : tiles) {
                byte[] writeB = t.getTileData();
                //System.err.println("Writing tile with tileData size: " + t.getTileData().length);
                fos.write(writeB);
            }

//            for (byte[] b : textures_and_blocks) {
//                fos.write(b);
//            }


            fos.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void write_dbarray(byte[][] in, FileOutputStream writer) throws IOException {
        for (int i = 0; i < in.length; i++) {
            writer.write(in[i]);
        }
    }

    public static int readCInt(byte[] input) throws IOException {
        ByteArrayInputStream bis = new ByteArrayInputStream(input);
        DataInputStream in = new DataInputStream(bis);
        long retint = 0;
        for (int i = 0; i <
                4; i++) {
            int j = in.readUnsignedByte();
            retint +=
                    j * (Math.pow(2, i * 8));
        }

        if (retint > 2147483647) {
            retint -= 2147483647;
            retint -=
                    2147483647;
            retint -=
                    2;
        }

        return (int) retint;
    }

    public static byte[] inttoBarray(int number) {
        byte[] intByte = new byte[4];
        for (int i = 0; i < 4; i++) {
            intByte[i] = (byte) (number >> (8 * i));
        }
        return intByte;
    }

    public static float readCFloat(byte[] input) throws IOException {
        ByteArrayInputStream bis = new ByteArrayInputStream(input);
        DataInputStream in = new DataInputStream(bis);
        return in.readFloat();
    }

    private static BufferedImage getImagefromByteArray(byte[] barray, int sizex, int sizey) throws IOException {
        BufferedImage bufferedImage = new BufferedImage(sizex, sizey, BITYPE);

        int i = 0;
        for (int y = 0; y < sizey; y++) {
            for (int x = 0; x < sizex; x++) {
                byte[] b = new byte[4];
                b[2] = barray[i];
                b[1] = barray[i + 1];
                b[0] = barray[i + 2];
                b[3] = barray[i + 3];
                bufferedImage.setRGB(x, y, readCInt(b));
                i += 4;
            }
        }
        return bufferedImage;
    }

//    //intent was to draw a map of the level.
//    private static void drawMap(byte[][] grid) throws IOException {
//        BufferedImage bufferedImage = new BufferedImage(8192, 8192, BITYPE);
//        Graphics2D g2d = bufferedImage.createGraphics();
//
//        for (int y = 0; y < 256; y++) {
//            for (int x = 0; x < 256; x++) {
//                int color = Math.min(255, grid[(y * 256) + x][0] * 10);
//                g2d.setColor(new Color(color, color, color));
//                g2d.fillRect(x * 32, y * 32, 32, 32);
//                //grid[(y * 256) + x][0];
//            }
//        }
//
//
//        File f = new File("map.png");
//        ImageIO.write(bufferedImage, "png", f);
//    }
//
//    public static BufferedImage toBufferedImage(Image i) {
//        if (i instanceof BufferedImage) {
//            return (BufferedImage) i;
//        }
//        Image img;
//        img = new ImageIcon(i).getImage();
//        BufferedImage b;
//        b = new BufferedImage(img.getWidth(null), img.getHeight(null), BITYPE);
//        Graphics g = b.createGraphics();
//        g.drawImage(img, 0, 0, null);
//        g.dispose();
//        return b;
//    }


    public void extract_and_convert(ArrayList<MD5db> md5dbs) throws IOException {
        if (readCInt(version) == 10) {
            version = inttoBarray(11);

            File dir = new File("texture/converted");
            if (!dir.exists()) {
                System.out.println("Making directory texture/converted");
                dir.mkdir();
            }

            try {

                for (Tile t : tiles) {
                    if (t.get("sizex") != null && t.get("sizey") != null && t.get("textureblob") != null) {


                        int sizex = readCInt(t.get("sizex"));
                        int sizey = readCInt(t.get("sizey"));
                        if (sizex > 0) {
                            if (t.get("filename") == null) {
                                byte[] texdata = t.get("textureblob");
                                if (texdata != null) {
                                    BufferedImage image = getImagefromByteArray(texdata, sizex, sizey);
                                    String md5 = getMD5fromImage(image);
                                    String filenameTo = "";
                                    String tempString;
                                    boolean success = false;
                                    for (MD5db m : md5dbs) {
                                        if (!success) {
                                            tempString = m.getFile(md5);
                                            if (tempString != null) {
                                                filenameTo = tempString;
                                                success = true;
                                            }
                                        }
                                    }
                                    if (!success) {
                                        filenameTo = "texture/converted/" + md5 + ".png";
                                        saveImage(image, filenameTo);
                                    }

                                    //Image saved, or reference caught.

                                    if (filenameTo.startsWith("texture/")) {
                                        filenameTo = filenameTo.substring("texture/".length());
                                    }
                                    //System.err.println("Filenameto: " + filenameTo);
                                    t.put("sizex", inttoBarray(0 - filenameTo.length()));
                                    t.put("sizey", null);
                                    t.put("textureblob", null);
                                    t.put("magfilter", null);
                                    t.put("minfilter", null);
                                    t.put("filename", filenameTo.getBytes());
                                }
                            }
                        }
                    }
                }

            } catch (Exception e) {
                e.printStackTrace();
            }
        } else {
            System.err.println("WARNING: Cannot convert: level is version " + readCInt(version) + " instead of 10");
        }
    }

    public static String getMD5fromImage(BufferedImage image) throws IOException, NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("MD5");

        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        ImageIO.write(image, "png", baos);
        md.update(baos.toByteArray());

        //byte[] data = ((DataBufferByte)image.getData().getDataBuffer()).getData();
        //md.update(data);
        BigInteger bi = new BigInteger(1, md.digest());
        return bi.toString(16);
    }

    public static void saveImage(BufferedImage image, String path) throws IOException {
        ImageIO.write(image, "png", new File(path));
    }
}
