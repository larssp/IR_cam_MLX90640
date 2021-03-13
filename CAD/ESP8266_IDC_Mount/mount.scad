//use <../ESP8266/ESP8266_HW-463.scad>;
//rotate([0,0,90]) ESP8266_HW463();

module one_connector()
{
    union()
    {
        import("../IDC_40P_connector/3417-6640.stl");
        cube([6.1,55.7,6],center=false);
    }
}

module connectors()
{
    // EN side
    color("Green", 0.2) 
    translate([
    19.15,
    -8.4, // half pin distance (to get pin on origin). 
    -0.8-2.7 // half pcb thickness + pin black cube
    ]) 
    rotate([180,0,-90]) 
    one_connector();
    
    translate([
    -3.5*2.54+0.4,
    0.5*2.54-5*2.54, // half pin distance (to get pin on origin). 
    -0.8-2.75/2 // half pcb thickness + pin black cube
    ])
    cube([55.75,6,2.75],center=true);


    // 3V3 Side
    color("Green", 0.2) 
    mirror([0,1,0])
    translate([
    19.15,
    -8.4, // half pin distance (to get pin on origin). 
    -0.8-2.7 // half pcb thickness + pin black cube
    ]) 
    rotate([180,0,-90]) 
    one_connector();
    
    translate([
    -3.5*2.54+0.4,
    -0.5*2.54+5*2.54, // half pin distance (to get pin on origin). 
    -0.8-2.75/2 // half pcb thickness + pin black cube
    ])
    cube([55.75,6,2.75],center=true);
}

module mount()
{
    translate([-6.50,0,-0.81-7/2])
    cube([65,33,7],center=true);
}

module mountingholes()
{
    translate([0,0,4]) rotate([0,0,90]) 
    {
        $fn=72;
            translate([-28.75/2+2.5,-52/2+2.675,0]) cylinder(d=2.85,h=32,center=true);
            translate([28.75/2-2.5,-52/2+2.675,0]) cylinder(d=2.85,h=32,center=true);
    }
    
    translate([0,0,-9.9+2.5]) rotate([0,0,90]) 
    {
        $fn=6;
            translate([-28.75/2+2.5,-52/2+2.675,0]) {
                cylinder(d=6.1,h=4,center=true);
                translate([0,-3.1,0]) cube([6.1,6.1,4],center=true);
            }
            translate([28.75/2-2.5,-52/2+2.675,0]) 
            {
                cylinder(d=6.1,h=4,center=true);
                translate([0,-3.1,0]) cube([6.1,6.1,4],center=true);
            }
    }
}

module ESP8266_mount()
{
    union()
    {
        difference()
        {
            mount();
            connectors();
            mountingholes();
        };
        % connectors();
    }
}

ESP8266_mount();