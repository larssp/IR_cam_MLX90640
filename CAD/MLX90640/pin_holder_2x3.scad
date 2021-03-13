 use <MLX90640_FOV55.scad>
 
 module mlx90640_mount()
 {
     difference()
     {
         cube([17.5,17.5,22.5],center=true);
         color("Black",0.3) translate([0,0,-7.5]) cube([7.7,5.1,15],center=true);
         mlx90640();
         cylinder(d=9.25,h=25,center=true, $fn=72);
         translate([5,0,-7.1]) cube([1.5,1,15],center=true);
     }
    
     
 }
 
 
 mlx90640_mount();
 color("Black",0.3) translate([0,0,-7.5]) cube([7.7,5.1,15],center=true);
 mlx90640();