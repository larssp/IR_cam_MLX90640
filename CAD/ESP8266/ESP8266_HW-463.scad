module ESP8266_HW463()
{
    $fn=50;
    
    color("White", 1.0) translate([0,-15,0.5]) rotate([0,0,90]) text("HW-463", size=2);
    
    // pcb
    difference()
    {
        color("SteelBlue") minkowski()
        {
            cube([28.75-2*2.75,52.0-2*2.75,1.6/2], center=true);
            cylinder(r=2.75,h=1.6/2,center=true);
        };
        translate([28.75/2-2.5,52/2-2.675,0]) cylinder(d=2.85,h=1.7,center=true);
        translate([-28.75/2+2.5,52/2-2.675,0]) cylinder(d=2.85,h=1.7,center=true);
        translate([-28.75/2+2.5,-52/2+2.675,0]) cylinder(d=2.85,h=1.7,center=true);
        translate([28.75/2-2.5,-52/2+2.675,0]) cylinder(d=2.85,h=1.7,center=true);
    }
    
    // pcb plane clearance
    * color("Red", 0.2) minkowski()
    {
        cube([28.75-2*2.55,52.0-2*2.55,1.6], center=true);
        cylinder(r=2.75,h=1.6,center=true);
    }
    
    // pins
    pin(5*2.54,20,"D23",false);
    pin(5*2.54,20-1*2.54,"D22",false);
    pin(5*2.54,20-2*2.54,"TX0",false);
    pin(5*2.54,20-3*2.54,"RX0",false);
    pin(5*2.54,20-4*2.54,"D21",false);
    pin(5*2.54,20-5*2.54,"D19",false);
    pin(5*2.54,20-6*2.54,"D18",false);
    pin(5*2.54,20-7*2.54,"D5",false);
    pin(5*2.54,20-8*2.54,"TX2",false);
    pin(5*2.54,20-9*2.54,"RX2",false);
    pin(5*2.54,20-10*2.54,"D4",false);
    pin(5*2.54,20-11*2.54,"D2",false);
    pin(5*2.54,20-12*2.54,"D15",false);
    pin(5*2.54,20-13*2.54,"GND",false);
    pin(5*2.54,20-14*2.54,"3V3",false);
    
    pin(-5*2.54,20,"EN",true);
    pin(-5*2.54,20-1*2.54,"VP",true);
    pin(-5*2.54,20-2*2.54,"VN",true);
    pin(-5*2.54,20-3*2.54,"D34",true);
    pin(-5*2.54,20-4*2.54,"D35",true);
    pin(-5*2.54,20-5*2.54,"D32",true);
    pin(-5*2.54,20-6*2.54,"D33",true);
    pin(-5*2.54,20-7*2.54,"D25",true);
    pin(-5*2.54,20-8*2.54,"D26",true);
    pin(-5*2.54,20-9*2.54,"D27",true);
    pin(-5*2.54,20-10*2.54,"D14",true);
    pin(-5*2.54,20-11*2.54,"D12",true);
    pin(-5*2.54,20-12*2.54,"D13",true);
    pin(-5*2.54,20-13*2.54,"GND",true);
    pin(-5*2.54,20-14*2.54,"VIN",true);
    
    // ESP32 Module
    color("Silver") translate([28.75/2-22.4,1,0.8]) cube([15.7,17.7,4.78-1.6], center=false);
    color("Black")  translate([-9,19,0.8]) cube([18,6.5,1.1], center=false);
    
    // LEDs
    color("Red",0.7) translate([28.75/2-19.11,26-30.6,0.8]) cube([1,2,1], center=false);
    color("Blue",0.7) translate([28.75/2-10,26-30.6,0.8]) cube([1,2,1], center=false);
    
    // Buttons
    translate([28.75/2-22,-26+3.6,0.8]) 
    {
        color("Black") cylinder(r=0.9,h=1.7,center=true);
        color("White", 1.0) translate([2,-0.6,-0.4]) rotate([0,0,90]) text("EN", size=0.8);
        color("Black") translate([16,0,0]) cylinder(r=0.9,h=1.7,center=true);
        color("White", 1.0) translate([14.5,-1,-0.4]) rotate([0,0,90]) text("BOOT", size=0.8);
    }
    
    // USB Port
    color("Silver")  translate([28.75/2-18,-26.2,0.8]) cube([7.7,5.4,2.2], center=false);
    color("Red",0.5) translate([28.75/2-18,-26.2-10,0.8]) cube([7.7,5.4+10,2.2], center=false);
    
    module pin(x=0.0, y=0.0, desc="", mirror=false)
    {
     translate([x,y,0])
     {
        color("Goldenrod", 1.0) translate([0, 0, -11.33/2+2.46]) cube([0.65,0.65,11.33], center=true);
        color("Black", 1.0)     translate([0, 0, -1-2.54/2])     cube([2.54,2.54,2.54], center=true); 
        color("Red", 0.5)       translate([0, 0, -7.3])          cube([3,3,20], center=true);
         
        if (mirror) color("White", 1.0) translate([2.5,-1,0.4])   rotate([0,0,90]) text(desc, size=0.8);
        else        color("White", 1.0) translate([-1.7,-1,0.4])   rotate([0,0,90]) text(desc, size=0.8);
         
     }
    }    
}

ESP8266_HW463();