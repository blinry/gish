package gishleveltool;

import java.util.ArrayList;
import java.util.HashMap;

public class Tile {

    private HashMap<String, byte[]> hashmap;
    private static ArrayList<String> file_order;

    public Tile() {
        hashmap = new HashMap<String, byte[]>();
        if (file_order == null) {
            System.err.println("regenerating tile order stuff");
            file_order = new ArrayList<String>();
            file_order.add("sizex");
            file_order.add("filename");
            file_order.add("sizey");
            file_order.add("magfilter");
            file_order.add("minfilter");
            file_order.add("textureblob");
            file_order.add("block_numoflines");
            file_order.add("block_lines");
            file_order.add("block_friction");
            file_order.add("block_breakpoint");
            file_order.add("block_middamage");
            file_order.add("block_foredamage");
            file_order.add("block_density");
            file_order.add("block_drag");
            file_order.add("block_animation");
            file_order.add("block_animationspeed");
        }
    }

    public void put(String identifier, byte[] barray) {
        hashmap.put(identifier, barray);
    }

    public byte[] get(String identifier) {
        return hashmap.get(identifier);
    }

    public byte[] getTileData() {
        return getTileData(false);
    }

    public byte[] getTileData(boolean showfoo) {
        /*Set<String> temp = hashmap.keySet();
        temp.removeAll(file_order);
        for (String s : temp) {
        System.err.println("!!!!!! YOU FORGOT: " + s);
        }*/


        for (String s : file_order) {
            if (hashmap.get(s) != null) {
                if (showfoo) {
                    System.err.println("getTileData() has " + s + "  with length: " + hashmap.get(s).length);
                }
            } else {
                //System.err.println("getTileData() DOES NOT HAVE " + s);
            }
        }
        byte[] retb = new byte[0];
        for (String s : file_order) {
            if (hashmap.get(s) != null) {
                retb = Gishlevel.cat(retb, hashmap.get(s));
            }
        }
        //System.err.println("getTileData():  returned length:  " + retb.length);
        return retb;

    }
}
