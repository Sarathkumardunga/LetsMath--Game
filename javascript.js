var playing = false;
var score;
var action;
var timeremaining;
var correctAnswer;

//if we click in start/reset 
document.getElementById("startreset").onclick = function(){
    //if we are playing (in this case it will be reset button)
    if(playing == true){
        
        //Reload the page
        location.reload();
    }
    else{    //if we are not playing
        
        //U entered the playing mode.
        playing = true;
        //We have to hide the game over box
        hide("gameover");
        //set score to 0
        score = 0;
        document.getElementById("scorevalue").innerHTML = score;
        
        //show countdown box
        //document.getElementById("timeremaining").style.display = "block";
        show("timeremaining");
        timeremaining = 60;
        document.getElementById("timeremainingvalue").innerHTML = timeremaining;

        //change button text to reset
        document.getElementById("startreset").innerHTML = "Reset Game";
    
        //Start Countdown
        startCountdown();

        //Generate a new question and multiple ans
        generateQA();
    }
}

//Events to occur when we click on the ans box
for(i = 1; i < 5; i++){
    document.getElementById("box"+i).onclick = function(){
        //check if we are playing
        if(playing == true){
            if(this.innerHTML == correctAnswer){
                //u got the correct ans
                //Then increase the score by 1
                score++;
                document.getElementById("scorevalue").innerHTML = score;
                hide("wrong");
                show("correct");
                setTimeout(function(){
                    hide("correct");
                }, 1000);
    
                //if the choosen option is coect generate new question
                generateQA();
            }
            else{
                score -= 0.25;
                document.getElementById("scorevalue").innerHTML = score;
                hide("correct");
                show("wrong");
                setTimeout(function(){
                    hide("wrong");
                }, 1000);
            }
        }
    }
}
 
//reduce time by 1 sec in loops
function startCountdown(){
    action = setInterval(function(){
        timeremaining -= 1;
        document.getElementById("timeremainingvalue").innerHTML = timeremaining;
    
        if(timeremaining == 0){ //time over -> Gameover
            stopCountdown();   // stop the counter
            
            //Show the game over message
            //document.getElementById("gameover").style.display = "block";
            show("gameover");
            document.getElementById("gameover").innerHTML = "<p>Game Over!</p><p>Your score is "+ score +".</p>"
        
            //Also when the game is over, Hide the timer, correct box and try again box
            hide("timeremaining");
            hide("correct");
            hide("wrong");

            //Finally u have to change the playing mode to false
            playing = false;
            //And also change the reset Game to start game
            document.getElementById("startreset").innerHtml = "Start Game";
        }
    }, 1000);
}

//Function to stop the countdown
function stopCountdown(){
    clearInterval(action);
}

//Function to hide the box
function hide(Id){
    document.getElementById(Id).style.display = "none";
}
   
//Function to show the box
function show(Id){
    document.getElementById(Id).style.display = "block";
}

//Generate question and multiple ans
function generateQA(){
    var x = 1 + Math.round(Math.random() * 9);
    var y = 1 + Math.round(Math.random() * 9);

    correctAnswer = x*y;
    document.getElementById("question").innerHTML = x + "x" + y;

    var correctPosition = 1 + Math.round(Math.random() * 3);
    //we need to place the correct ans in the correct position of the box options.
    document.getElementById("box"+correctPosition).innerHTML = correctAnswer;

    //inorder to avoid dupicate same numbers in options as wrong ans
    var answers = [correctAnswer];

    //And fill the remaining answers with wrong ans
    for(i = 1; i < 5; i++){
        if(i != correctPosition){
            var wrongAnswer;
            //I should take care that wrong ans and correct ans should not be the same.
            do{
                wrongAnswer = ((1 + Math.round(Math.random() * 9)) * (1 + Math.round(Math.random() * 9)));
            }while(answers.indexOf(wrongAnswer) > -1)  /*while(wrongAnswer == correctAnswer)*///Also i need to ensure that the wrong answers are also unique in the boxes.
            
            document.getElementById("box" + i).innerHTML = wrongAnswer;
            answers.push(wrongAnswer);
        }
    }
}


