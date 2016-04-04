var circle;

function onLoad() {
    initLanding();
    setInterval(refresh, 5000);

    setInterval(function() {
        var second = new Date().getSeconds();
        circle.animate(second / 5, function() {
        });
    }, 1000);
}


function initLanding() {

    circle = new ProgressBar.Circle('#landing-progress', {
        color: "#FCB03C",
        strokeWidth: 1.5,
        trailColor: null,
        fill: "#FFF9F0"
    });

    // circle.animate(1, {
    //     duration: 5000,
    //     easing: 'easeInOut'
    // },function (){
    //     circle.set(0);
    // });

    
}

function refresh() {
    $.get("/arduino/temperature", function(data, status){
        if(status == "success"){
            var update = data.split(",");
            $("#temp").text(update[1]+"°C");
            $("#timestamp").text(update[2]);
            $("#tx").text(update[3]+"/"+update[4]);
            $("#dist").text(update[5]);
        }
        else {
            console.log('Failed to retrieve data from "/arduino/temperature".');
        }
    });
    //$('#content').load('/arduino/temperature');
    //$('#timestamp').load('/arduino/timestamp');
}



$(window).load(onLoad);
