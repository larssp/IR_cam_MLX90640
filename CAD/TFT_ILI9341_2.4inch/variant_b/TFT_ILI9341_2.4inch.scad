 // ILI9341 TFT LCD Module
 // the version, which was shipped from the ebay seller
 // Model Version ZH6 (?)
 
 module TFT_ILI9341()
 {
     union()
     {
         // board
         color("DarkRed", 1.0) translate([0,0,-0.5])
         cube([61,84,1.0], center=true);
         
         // push button K1
         translate([-1.5,38,0]) 
         {
             // case
             color("Silver", 1.0) cube([7.5,4,1.6], center=false);
             // button
             color("White", 1.0)  translate([(7.5-3.3)/2, (4-1.8)/2,0]) cube([3.3,1.8,1.8], center=false);
             // cut-out-box
             color("Red", 0.5)  translate([-3,-1.5,0]) cube([7.5+6,4+3,2.0], center=false);
             // silkscreen
             color("White", 1.0) translate([-10,-1.5,-0.49]) text("K1", size=4);
         }
         
         // TFT screen
         translate([-25.7,-36,0]) 
         {
             color("SlateGray", 1.0) cube([50,70,2.2], center=false);
             color("Red", 0.5) translate([-1, -1, 0]) cube([50+2,70+2,5.5], center=false);
         }
         
         
         // Pins
         translate([-29, -33, 0])
         {
             color("White", 1.0)
             {
                 translate([55,44,-0.51]) rotate([180,0,0]) text("J1", size=2);
                 translate([55,-2,-0.51]) rotate([180,0,0]) text("J2", size=2);
                 translate([-1,-2,-0.51]) rotate([180,0,0]) text("J3", size=2);
                 translate([-1,35,-0.51]) rotate([180,0,0]) text("J4", size=2);
             }
             
             pin(0,0*2.54,"n/c");
             pin(0,1*2.54,"LCD_RST");
             pin(0,2*2.54,"LCD_CS / Touch X-");
             pin(0,3*2.54,"LCD_RS / Touch Y+");
             pin(0,4*2.54,"LCD_WR");
             pin(0,5*2.54,"LCD_RD");
             
             pin(0,7*2.54,"n/c");
             pin(0,8*2.54,"GND");
             pin(0,9*2.54,"GND");
             pin(0,10*2.54,"5V");
             pin(0,11*2.54,"3V3");
             pin(0,12*2.54,"K1");
             
             translate([56.86, 0, 0])
             {
                 pin(0,0*2.54,"n/c",true);
                 pin(0,1*2.54,"n/c",true);
                 pin(0,2*2.54,"LCD_D2",true);
                 pin(0,3*2.54,"LCD_D3",true);
                 pin(0,4*2.54,"LCD_D4",true);
                 pin(0,5*2.54,"LCD_D5",true);
                 pin(0,6*2.54,"LCD_D6",true);
                 pin(0,7*2.54,"LCD_D7",true);
                 
                 translate([0, -1.016, 0]) // famous arduino header spacing error
                 {
                     pin(0,9*2.54,"Touch Y- / LCD_D0",true);
                     pin(0,10*2.54,"Touch X+ / LCD_D1",true);
                     pin(0,11*2.54,"SD_SS",true);
                     pin(0,12*2.54,"SD_DI",true);
                     pin(0,13*2.54,"SD_DO",true);
                     pin(0,14*2.54,"SD_SCK",true);
                     pin(0,15*2.54,"n/c",true);
                     pin(0,16*2.54,"n/c",true);
                 }
             }
         }
         
         
         // Micro Controller Chips
         translate([-29, -33+11*2.54, 0])
         color("Red", 0.5) translate([0, 0, -3.54]) cube([56.86,5*2.54,2.54], center=false);
         
         // SD Card Reader
         translate([-29, -33+3*2.54, 0]) 
         translate([14.66, 47.65+3.1, -4])
         {
             color("Silver", 1.0) difference()
             {
                 linear_extrude(3) 
                 polygon([ [0,0], [17,0], [17,16.65], [12,16.65], [10,16.0], [0,16.0]]);
                 
                 translate([0,1,0.5]) linear_extrude(2) 
                 polygon([ [1,0], [16,0], [16,16.65], [12,16.65], [10,16.0], [1,16.0]]);
             };
             
             color("Red", 0.5) translate([0,0,-0.2]) linear_extrude(3.2) 
             polygon([ [-1,-1], [18,-1], [18,30], [-1,30]]);
             
             color("Black", 1.0) translate([1,10,0]) rotate([180,0,0]) text("SD card", size=3);
         }

     }
 }
 
 
 module pin(x=0.0, y=0.0, desc="", mirror=false)
 {
     translate([x,y,0])
     {
        color("Goldenrod", 1.0) translate([0, 0, -11.33/2+2.46]) cube([0.65,0.65,11.33], center=true);
        color("Black", 1.0)     translate([0, 0, -1-2.54/2])     cube([2.54,2.54,2.54], center=true); 
        color("Red", 0.5)       translate([0, 0, -7.3])          cube([3,3,20], center=true);
         
        if (mirror) color("White", 1.0) translate([-2,1,-0.51]) rotate([180,0,0]) text(desc, size=1.5, halign="right");
        else        color("White", 1.0) translate([2,1,-0.51])   rotate([180,0,0]) text(desc, size=1.5);
         
     }
 }
 
 TFT_ILI9341();