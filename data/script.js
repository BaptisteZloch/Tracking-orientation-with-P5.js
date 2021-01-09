function setup() {
    var canvas = createCanvas(400, 400, WEBGL);
    canvas.parent('container');//store the canvas into a div with id='container'
}
//global variable : 3 axis
var x = 0;
var y = 0;
var z = 0;
setInterval(function getData() {
    //3 http request to get 3 angular orientation 
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "get_x", true);
    xhr.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            x = parseFloat(this.responseText);
        }
    };
    xhr.send();
    var xhr2 = new XMLHttpRequest();
    xhr2.open("GET", "get_y", true);
    xhr2.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            y = parseFloat(this.responseText);
        }
    };
    xhr2.send();
    xhr3.send();
    var xhr3 = new XMLHttpRequest();
    xhr3.open("GET", "get_z", true);
    xhr3.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            z = parseFloat(this.responseText);
        }
    };
    xhr3.send();
}, 100);
function draw() {
    background(20); //tone of the backgroud behind our figure
    console.log("y : " + y); //DEBUG
    console.log("x : " + x); //DEBUG
    console.log("z : " + z); //DEBUG
    //rotate the figure from our real orientation
    rotateX(x);
    rotateY(y);
    rotateY(z);
    //the figure is a box 
    box(100, 50, 100);
}  