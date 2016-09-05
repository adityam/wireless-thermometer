var circle;

constrain = function (v, min, max) {
    if (v < min) {
        return min;
    } else if (v > max) {
        return max;
    } else {
        return v;
    }
};

/**
 * Battery class.
 */
Battery = function (element, opt_level) {
    this.level = constrain(opt_level || 100, 0, 100)
    this.element = element;
    element.addClass('ui-batt')
        .html($("<div class='ui-batt-level'></div>").width(this.getWidth_()))
        .append("<div class='ui-batt-text'></div><div class='ui-batt-point'></div>")
        .attr("data-level", this.level);
    this.battLevel = $('.ui-batt-level', element);
    this.battText = $('.ui-batt-text', element);
    this.updateLevelClasses_();
};

Battery.prototype.setLevel = function (level) {
    this.level = constrain(level, 0, 100);
    this.updateLevelClasses_();
    this.element.attr('data-level', this.level);
    this.battLevel.width(this.getWidth_());
    this.battText.html(this.level + '%');
};

Battery.prototype.getWidth_ = function () {
    return 40 * (this.level / 100);
};

Battery.prototype.updateLevelClasses_ = function () {
    this.element.removeClass('ui-batt-level-a ui-batt-level-b ui-batt-level-c ui-batt-level-d');
    var level = this.level;
    if (level < 20) {
        this.element.addClass('ui-batt-level-a');
    } else if (level < 45) {
        this.element.addClass('ui-batt-level-b');
    } else if (level < 70) {
        this.element.addClass('ui-batt-level-c');
    } else if (level <= 100) {
        this.element.addClass('ui-batt-level-d');
    }
};

/**
 * Example of use
 */
var battery = new Battery($('#battery-icon'), 100);

// setInterval(function () {
//     battery.setLevel(battery.level - 1);
// }, 100);


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
            battery.setLevel(Math.round( ( parseFloat(update[4]) - parseFloat(update[3]) ) / parseFloat(update[4])*100) );
        }
        else {
            console.log('Failed to retrieve data from "/arduino/temperature".');
        }
    });
    //$('#content').load('/arduino/temperature');
    //$('#timestamp').load('/arduino/timestamp');
}



$(window).load(onLoad);







