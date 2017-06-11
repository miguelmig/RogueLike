
$(document).keyup(function (e)
{
    var windowsDestination = "";
    switch(e.which)
    {
    case 37:
    case 38:
    case 39:
    case 40:
        windowsDestination = getArrowLink(e.which);
        if(windowsDestination == "")
        {
            windowsDestination = getExitHyperlink();
        }
        break;
    case 82:
        windowsDestination = "?restart";
    }

    if (windowsDestination != "")
    {
        window.location = windowsDestination;
    }
});

function getArrowLink(key)
{
    var id = "";
    switch(key)
    {
        case 37:
            id = 'arrow-left';
            break;
        case 38:
            id = 'arrow-up';
            break;
        case 39:
            id = 'arrow-right';
            break;
        case 40:
            id = 'arrow-down';
            break;
        
    }
    var elem = document.getElementById(id);
    if(elem == null)
    {
        return "";
    }

    return elem.href.animVal;
}

function getExitHyperlink()
{
    var elem = document.getElementById("exit");
    if(elem == null)
    {
        return "";
    }

    return elem.href.animVal;
}

function restart()
{
    window.location = "?restart";
}

function load()
{
    var restartButton = document.getElementById('restart');
    if(restartButton)
    {
        restartButton.onclick = restart;
    }

    hBar = $('.health-bar');
    var bar = hBar.find('.bar');
    var total = hBar.data('total'),
        value = hBar.data('value');
    var barWidth = (value / total) * 100;
    bar.css('width', barWidth + "%");
}

function on_damage(damage)
{
    hBar = $('.health-bar'),
    bar = hBar.find('.bar'),
    hit = hBar.find('.hit');

    var total = hBar.data('total'),
        value = hBar.data('value');
    
    if (value < 0) {
        return;
    }

    var newValue = value;
    // calculate the percentage of the total width
    var barWidth = (newValue / total) * 100;
    var hitWidth = (damage / value) * 100 + "%";
    
    // show hit bar and set the width
    hit.css('width', hitWidth);
    setTimeout(function(){
      hit.css({'width': '0'});
      bar.css('width', barWidth + "%");
    }, 500);
    //bar.css('width', total - value);
}

function on_game_over(score)
{
    alert("Perdeste o jogo com a pontuação de " + score + "!");
}