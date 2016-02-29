import { countryStatus } from './data/countryStatus.js';

export var helpers = {
    style:  function (feature) {
        return {
                weight: 1,
                opacity: 1,
                color: '#ccc',
                fillOpacity: 1,
                fillColor: helpers.getColor(feature)
            };
    },
    getColor: function(feature) {
        var country = countryStatus.find(function(v){ return v.ISO3 === feature.id;});

        if(country !== undefined) {
            switch(country.EITI_Status) {
                case 1:
                    return '#65c32d';
                    break;
                case 2:
                    return '#42abd8';
                    break;
                case 3:
                    return '#ff6600';
                    break;
                case 4:
                    return '#dddddd';
                    break;
            }
        }
        else
        {
            return '#dddddd';
        }
    },
    showTooltip: function (e) {
        var layer = e.target;
        var country = countryStatus.find(function(v){ return v.ISO3 === layer.feature.id;});

        var country_url = (country.enabled) ? 'country_' + country.ISO3 + '.html':'countries.html';

        var popup = L.popup({autoPan:false, closeButton:false})
            .setLatLng(e.latlng)
            .setContent('<a href="' + country_url + '"><strong>' + layer.feature.properties.name + '</strong>')
            .openOn(layer._map);
    },

    resetTooltip: function(e) {
    // Left for future reference
    },


    zoomToFeature: function(e){
        window.location = 'country_' + layer.feature.id + '.html';
    },

    onEachFeature: function (feature, layer) {
        layer.on({
            mouseover: helpers.showTooltip,
            mouseout: helpers.resetTooltip,
            click: helpers.zoomToFeature
        });
    },
    addLegend: function(e) {
        var info = L.control({position: 'bottomleft'});
        var map = e.target._map;

        info.onAdd = function (map) {
            if(map.options.legend === undefined) {
                map.options.legend = L.DomUtil.create('div', 'info legend');
                this.update();
            }
            return map.options.legend;
        };

        info.update = function (props) {
            map.options.legend.innerHTML = ('<i style="background:#42abd8"></i> <strong>EITI Candidate Country</strong> <br/>implementing EITI, not yet compliant <br/>') + 
                ('<i style="background:#65c32d"></i> <strong>EITI Compliant Country</strong><br/>confirmed to have met all EITI requirements <br/>') + 
                ('<i style="background:#ff6600"></i> <strong>Suspended</strong><br/>Compliant/Candidate status is temporarily suspended <br/>') + 
                ('<i style="background:#dddddd"></i> Other <br/>');
        };

        info.addTo(map);
    }



};

