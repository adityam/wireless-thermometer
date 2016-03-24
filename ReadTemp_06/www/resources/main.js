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
    $('#content').load('/arduino/temperature');
}



$(window).load(onLoad);
