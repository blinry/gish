package gishleveltool;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class ImagePanel extends JPanel {

    private static ArrayList<Color> colors;
    private static int colorindex = 0;
    private JPanel parentpanel;
    public BufferedImage image;
    private String filename;
    private JTextField textField;
    public String bottomtext;

    private MD5dbmaker parentmaker;

    public ImagePanel(final MD5dbmaker parentmaker, JPanel parentpanel, final String imagepath, int width, int height, final boolean clickable) throws IOException, NoSuchAlgorithmException {
        this.parentmaker = parentmaker;

        if (colors == null) {
            colors = new ArrayList<Color>();
            colors.add(Color.gray);
            colors.add(Color.red);
            colors.add(Color.blue);
            colors.add(Color.green);
            colors.add(Color.black);
            colors.add(Color.white);
        }

        File f = new File(".");
        this.filename = imagepath;
        //System.err.println("ARGH: " +f.getCanonicalPath() + md5db_maker.sep + imagepath);
        this.image = ImageIO.read(new File(f.getCanonicalPath() + "/" + imagepath));
        this.parentpanel = parentpanel;
        this.parentpanel.add(this);
        setBackground(Color.MAGENTA);
        setSize(width, height + MD5dbmaker.TEXTFIELD_HEIGHT);
        this.setVisible(true);
        this.setLayout(null);

        //bottomtext = Gishlevel.getMD5fromImage(image);
        bottomtext = imagepath;
        textField = new JTextField(bottomtext);
        textField.setLayout(null);
        textField.setEditable(false);
        textField.setFont(new Font("Arial", Font.PLAIN, 10));
        textField.setSize(MD5dbmaker.IMAGE_SIZE, MD5dbmaker.TEXTFIELD_HEIGHT);
        textField.setLocation(0, MD5dbmaker.IMAGE_SIZE);
        textField.setAlignmentY(BOTTOM_ALIGNMENT);

        this.add(textField);



        this.addMouseListener(new MouseListener() {

            public void mouseClicked(MouseEvent e) {
                if (e.getButton() == MouseEvent.BUTTON1) {
                    if (clickable) {
                        parentmaker.addEntry(filename);
                        //System.err.println("CLICKED ON:  " + filename);
                        if (e.isShiftDown()) {
                            //System.err.println("SHIFT IS ON");
                            try {
                                bottomtext = imagepath + " - " + Gishlevel.getMD5fromImage(image);
                                textField.setText(bottomtext);
                            } catch (IOException ex) {
                                Logger.getLogger(ImagePanel.class.getName()).log(Level.SEVERE, null, ex);
                            } catch (NoSuchAlgorithmException ex) {
                                Logger.getLogger(ImagePanel.class.getName()).log(Level.SEVERE, null, ex);
                            }
                        }
                    }
                } else {
                    colorindex += 1;
                    if (colorindex >= colors.size()) {
                        colorindex = 0;
                    }
                    setBackground(colors.get(colorindex));
                }
            }

            public void mousePressed(MouseEvent e) {
                //throw new UnsupportedOperationException("Not supported yet.");
            }

            public void mouseReleased(MouseEvent e) {
                //throw new UnsupportedOperationException("Not supported yet.");
            }

            public void mouseEntered(MouseEvent e) {
                setBackground(colors.get(colorindex));
                if (clickable) {
                    setBorder(BorderFactory.createLineBorder(Color.red, 3));
                }
            }

            public void mouseExited(MouseEvent e) {
                setBackground(Color.MAGENTA);
                if (clickable) {
                    setBorder(BorderFactory.createCompoundBorder());
                }
            }
        });
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        dopaint(g);
    }

    private void dopaint(Graphics g) {
        g.drawImage(image, 0, 0, MD5dbmaker.IMAGE_SIZE, MD5dbmaker.IMAGE_SIZE, this);
        //System.err.println("Refresh at " + System.currentTimeMillis());
    }
}
