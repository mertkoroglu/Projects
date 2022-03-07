var character = document.getElementById("character");
var block = document.getElementById("block");
var GameOver = document.getElementById("gameover");
var scoreBoard = document.getElementById("score");

var score = 0;
var colided = 0;
function jump(){
    //adds animate class to character object
    character.classList.add("animate");
    //after defined time removes the animate class
    setTimeout(function(event){
        character.classList.remove("animate");
    }, 500 );
}


function died(){
    block.style.animation="none";
    GameOver.style.display = "inherit";
}

let isAlive = setInterval(function(){

    //Gets top element of dino
    let dinoTop = parseInt(window.getComputedStyle(character).getPropertyValue("top"));
    //Gets left element of cactus
    let cactusLeft = parseInt(window.getComputedStyle(block).getPropertyValue("left"));


    //checks the collision
    if(cactusLeft < 20 && cactusLeft > 0 && dinoTop >= 140){
        died();
        colided = 1;
    }

    if(colided != 1){
        score++;
        scoreBoard.innerHTML = `Score: ${score}`;

    }


}, 10)


//if space bar pressed jump happens
document.addEventListener("keydown", function(event) {
   jump();
   

   if(block.style.animation === "none"){
    start();
}
  });