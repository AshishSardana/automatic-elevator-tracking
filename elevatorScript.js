//Elevator IOT Code

var button2 = document.getElementById("elevator");
button2.onclick = function(){
    
    // Create a request object
    var request = new XMLHttpRequest();
	
    //Capture the response and store it in a variable
	request.onreadystatechange = function () {
		if(request.readyState === XMLHttpRequest.DONE){
			//Take some action
			if(request.status === 200){
				var data = request.responseText;
				var span = document.getElementById('floor');
				span.innerHTML = data.toString();
			}
		}
			//Not done yet
	}
	
    //Make the request
	request.open('GET', 'https://api.thingspeak.com/channels/179562/fields/1/last.txt', true);
	request.send(null);  
};
