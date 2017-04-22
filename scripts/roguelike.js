
$(document).keydown(function (e)
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
}