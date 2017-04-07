/******************************* 
* scripts.js for mashup cs50 mother program application.py
* Programmeren 02 - pset 08 - exercise 01 
* By Maxim Stomphorst
 *******************************/

// Google Map
var map;

// markers for map
var markers = [];

// info window
var info = new google.maps.InfoWindow();

// execute when the DOM is fully loaded
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    var styles = [

        {
            featureType: 'administrative.land_parcel',
            elementType: 'labels',
            stylers:
                { visibility: 'on' }
        }
    ];

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    var options = {
        center: {lat: 52.5, lng: 5.75},
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 9,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    var canvas = $('#map-canvas').get(0);

    // instantiate map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, 'idle', configure);

});

/**
 * Adds marker for place to map.
 */
function addMarker(place, timeout)
{

    // calling timeout function for drop effect (visual)
    window.setTimeout(function() {

        // creating a marker 
        var marker = create_marker(place);
        
        // storing the marker for later use (remove)
        markers.push(marker);

        // lissening for click
        marker.addListener('click', function() {
    
            // oppening info windows with loading icon
            showInfo(marker, '<IMG BORDER="0" ALIGN="Center" SRC="static/ajax-loader.gif">');
            
            // getting the JSON formatted data
            $.getJSON('/articles?geo=' + place.postal_code).done (function (news_data) {
    
                // closing loading infowindows and opening with:
                // the het news rendert in HTML
                showInfo(marker, renderHTML(news_data));
            });
        });
    }, timeout);
    
    var geocoder = new google.maps.Geocoder();

    document.getElementById('submit').addEventListener('click', function() {
        geocodeAddress(geocoder, map);
    });
}
    


/**
 * Configures application.
 */
function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, 'dragend', function() {

        // if info window isn't open
        // http://stackoverflow.com/a/12410385
        if (!info.getMap || !info.getMap())
        {
            update();
        }
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, 'zoom_changed', function() {
        update();
    });

    // configure typeahead
    $('#q').typeahead({
        highlight: false,
        minLength: 1
    },
    {
        display: function(suggestion) { return null; },
        limit: 10,
        source: search,
        templates: {
            suggestion: Handlebars.compile(
            '<div>' +
               '<div>{{place_name}}, {{admin_name}}, {{postal_code}}</div>' +
            '</div>'
            )
        }
    });

    // re-center map after place is selected from drop-down
    $('#q').on('typeahead:selected', function(eventObject, suggestion, name) {

        // set map's center
        map.setCenter({lat: parseFloat(suggestion.latitude), lng: parseFloat(suggestion.longitude)});

        // update UI
        update();
    });

    // hide info window when text box has focus
    $('#q').focus(function(eventData) {
        info.close();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener('contextmenu', function(event) {
        event.returnValue = true;
        event.stopPropagation && event.stopPropagation();
        event.cancelBubble && event.cancelBubble();
    }, true);

    // update UI
    update();

    // give focus to text box
    $('#q').focus();
}

/**
 * Removes markers from map.
 */
function removeMarkers()
{
    // looping though array deleting the marker
    for (var i = 0; i < markers.length; i++) {
           markers[i].setMap(null);
    }

    // emptying the markers array
    markers = [];
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, syncResults, asyncResults)
{
    // get places matching query (asynchronously)
    var parameters = {
        q: query
    };
    $.getJSON(Flask.url_for('search'), parameters)
    .done(function(data, textStatus, jqXHR) {

        // call typeahead's callback with search results (i.e., places)
        asyncResults(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());

        // call typeahead's callback with no results
        asyncResults([]);
    });
}

/**
 * Shows info window at marker with content.
 */
function showInfo(marker, content)
{
    // start div
    var div = '<div id="info">';
    if (typeof(content) == 'undefined')
    {
        // http://www.ajaxload.info/
        div += '<img alt="loading" src="/static/ajax-loader.gif"/>';
    }
    else
    {
        div += content;
    }

    // end div
    div += '</div>';

    // set info window's content
    info.setContent(div);

    // open info window (if not already open)
    info.open(map, marker);
}

/**
 * Updates UI's markers.
 */
function update()
{
    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + ',' + ne.lng(),
        q: $('#q').val(),
        sw: sw.lat() + ',' + sw.lng()
    };
    $.getJSON(Flask.url_for('update'), parameters)
    .done(function(data, textStatus, jqXHR) {

       // remove old markers from map
       removeMarkers();

       // add new markers to map
       for (var i = 0; i < data.length; i++)
       {
           addMarker(data[i], i * 200);
       }
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
}

/**
 * Creats a unordered list with links in html
 */
function renderHTML(data) 
{

    // initiating unorderlist
    var htmlString = '<ul>';

    // gowing though array creating a link and the tag
    for (var i = 0; i < data.length; i++) 
    {
        htmlString += '<li>' + '<a href="' + data[i].link + '"' + 'target="_blank>Visit' + data[i].title + '</a></li>';
    }

    // closing the unorderlist
    htmlString += '</ul>';

    // sending back the HTML
    return htmlString;
}

/**
 * Creates a marker.
 * 
 * input a object with at least a:
 * latitude, longitude and a place_name.
 * 
 * output is a marker for googlemaps API
 */
function create_marker(place)
{
    // creating a marker and giving it propertys
    var marker = new google.maps.Marker ({
        position: {lat: place.latitude, lng: place.longitude},
        label: place.place_name,
        animation: google.maps.Animation.DROP,
        icon:{
            url:'static/pin.svg',
            scaledSize: new google.maps.Size(30,32),
            labelOrigin: new google.maps.Point(13,42),
        },
        map: map,
    });
    
    // returning the marker     
    return marker;
}

function geocodeAddress(geocoder, resultsMap) 
{
var address = document.getElementById('address').value;
    geocoder.geocode({'address': address}, function(results, status) {
    if (status === 'OK') {
        resultsMap.setCenter(results[0].geometry.location);
            
        var marker = new google.maps.Marker({
            map: resultsMap,
            position: results[0].geometry.location
        });
        
      } else {
        alert('Geocode was not successful for the following reason: ' + status);
      }
});
}