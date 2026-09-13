
document.getElementById("left").addEventListener("mousedown",function(){
    console.log("left click");
    
    fetch("http://192.168.1.34:80/control_left");});


document.addEventListener("mouseup",function(){
    //console.log("stop");
    fetch('http://192.168.1.34:80/control_stop');});

document.getElementById("right").addEventListener("mousedown",function(){
    console.log("right click");
    
    fetch("http://192.168.1.34:80/control_right");});

document.getElementById("btun").addEventListener("click",function(){
    console.log("capture");
    fetch("/capture");});

/*if(a==1 && b==1){
    console.log("stop");
    fetch('http://192.168.1.34:80/control_stop')
}*/
