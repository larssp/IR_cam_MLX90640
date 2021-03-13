// MLX90640 
// 55° FOV model

module mlx90640()
{
    union()
    {
        // baseplate
        color( "Goldenrod", 1.0 ) 
        {
            cylinder(0.4,r1=4.57,r2=4.57,center=false,$fn=72);
            translate([4,-0.4,0]) cube([1.46,0.8,0.4], center=false); // nodge
        }
        
        // GND pin
        color( "Goldenrod", 1.0 ) translate([-5.84/2*cos(22.5),-5.84/2*sin(22.5),-6]) 
        cylinder(6.0,d1=0.45,d2=0.45,center=false,$fn=24);
        
        // VDD pin
        translate([-5.84/2*cos(22.5),5.84/2*sin(22.5),0]) 
        union()
        {
            color( "Black", 1.0 ) translate([0,0,-0.1]) 
            cylinder(0.1,d1=0.7,d2=0.7,center=false,$fn=24);
            color( "Goldenrod", 1.0 ) translate([0,0,-6])  
            cylinder(6.0,d1=0.45,d2=0.45,center=false,$fn=24);
        };
        
        // SDA pin
        translate([5.84/2*cos(22.5),5.84/2*sin(22.5),0]) 
        union()
        {
            color( "Black", 1.0 ) translate([0,0,-0.1]) 
            cylinder(0.1,d1=0.7,d2=0.7,center=false,$fn=24);
            color( "Goldenrod", 1.0 ) translate([0,0,-6])  
            cylinder(6.0,d1=0.45,d2=0.45,center=false,$fn=24);
        };
        
        // SCL pin
        translate([5.84/2*cos(22.5),-5.84/2*sin(22.5),0]) 
        union()
        {
            color( "Black", 1.0 ) translate([0,0,-0.1]) 
            cylinder(0.1,d1=0.7,d2=0.7,center=false,$fn=24);
            color( "Goldenrod", 1.0 ) translate([0,0,-6])  
            cylinder(6.0,d1=0.45,d2=0.45,center=false,$fn=24);
        };
        
        
        // Capsule
        color( [41/255, 1/255, 24/255] ) 
        {
            rotate_extrude($fn=72) difference()
            {
                polygon(points = [ [3.0,  0.8], [4.65, 0.8], [4.65, 11.25],  [3.0,  11.25]]); // base rectangle
                polygon(points = [ [4.65+0.1, 11.25+0.1],  [4.65-0.5, 11.25], [4.65, 11.25-0.5]]);    // top chamfer
                translate([4.65+0.21,9.75,0]) circle(0.75, $fn=24); 
            };
            difference()
            {
                translate([0,0,1.3]) cylinder(9.9,r1=3.2,r2=3.2,center=false,$fn=72);
                translate([0,0,1.4]) cylinder(11,r1=3.1,r2=3.1,center=false,$fn=72);
            };
        }
        
        // Lense
        color( "Silver", 1.0 )
        {
            translate([0,0,0.4]) cylinder(0.4,r1=4.5,r2=4.5,center=false,$fn=72);
            translate([0,0,0.8]) difference()
            {
                sphere(d = 3.9,$fn=24);
                translate([0,0,-3.9/2]) cube(size=3.9,center=true);
            }
        };
        color("White", 0.1) translate([0,0,1.4]) 
        cylinder(9.81,r1=3.1,r2=3.1,center=false,$fn=72);

        
        // pin description
        translate([0,-0.6,0.4]) color( "Black", 1.0 ) rotate([180,0,180])
        {
            translate([-3.5,-1.5,0]) text("SCL", size = 0.5);
            translate([-3.5,2.2,0])  text("SDA", size = 0.5);
            translate([ 2.0,2.2,0])  text("VDD", size = 0.5);
            translate([ 2.0,-1.5,0]) text("GND", size = 0.5);
        };
    }
}

mlx90640();