

$(document).keydown(function (e)
{
    var windowsDestination;
    if(e.which == 38)
    {
        var up = document.getElementById('arrow-up');
        if(up == null)
        {
            return;
        }

        windowsDestination = up.href.animVal;
    }
    else if(e.which == 40)
    {
        var down = document.getElementById('arrow-down');
        if(down == null)
        {
            return;
        }

        windowsDestination = down.href.animVal;
    }
    else if(e.which == 39)
    {
        var right = document.getElementById('arrow-right');
        if(right == null)
        {
            return;
        }

        windowsDestination = right.href.animVal;
    }
    else if(e.which == 37)
    {
        var left = document.getElementById('arrow-left');
        if(left == null)
        {
            return;
        }

        windowsDestination = left.href.animVal;
    }
    else
    {
        return;
    }
    window.location = windowsDestination;
});

