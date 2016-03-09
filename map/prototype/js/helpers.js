var linkMap = {
    "ALB" : 1,
    "PHL" : 2, 
    "GHA" : 4,
    "COD" : 5,
    "PER" : 6, 
    "MNG" : 7
};

export var helpers = {

    getPaletteDivergent: function(index) {
        var colors = ['#42abd8', '#65c32d', '#ff6600', '#dddddd'];
        return colors[index];

    },
    getPaletteBreaks: function(index) {
        var colors = ['#f1eef6','#bdc9e1','#74a9cf','#2b8cbe','#045a8d'];
        return colors[index];
    },

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
        if(feature !== undefined) {
            //console.log(feature.indicator_value);
            if(feature.indicator_type == 'fixed') {
                var completeType = feature.metadata.find(function(v){ return (v.id == feature.indicator_value)})
                return completeType.color;
            }
            else
            {
                //debugger;
                if (feature.metadata === undefined) return;

                if(this.isNumeric(feature.indicator_value)) {
                    var value = Number(feature.indicator_value);
                    var completeType = feature.metadata.find(function(v){ 
                        return value > v.range.start && value <= v.range.end;
                        //return (value > v.range.start && value =< v.range.end);
                    });

                    return completeType !== undefined ? completeType.color : '#dddddd';

                }
                else
                {
                    return '#dddddd';
                }
                
            }
        }
        else
        {
            return '#dddddd';
        }
    },

    isNumeric: function( obj ) {
        return !jQuery.isArray( obj ) && (obj - parseFloat( obj ) + 1) >= 0;
    },

    showTooltipStatus: function (e) {
        var country_link = '';
        var layer = e.target;
        var country_status = layer.feature.indicator_value;
        var country_url = (country_status < 4 && linkMap[layer.feature.id]) ? '/implementing_country/' + linkMap[layer.feature.id] + '':'';
        if(country_url === '') {
            country_link = '<strong>' + layer.feature.properties.name + '</strong>';
        }
        else
        {
            country_link = '<a href="' + country_url + '"><strong>' + layer.feature.properties.name + '</strong></a>';
        }
        var popup = L.popup({autoPan:false, closeButton:false})
            .setLatLng(e.latlng)
            .setContent(country_link)
            .openOn(layer._map);
    },

    resetTooltip: function(e) {
    // Left for future reference
    },

    zoomToFeature: function(e){
        window.location = 'country_' + layer.feature.id + '.html';
    },

    onEachFeatureStatus: function (feature, layer) {
        layer.on({
            mouseover: helpers.showTooltipStatus,
            mouseout: helpers.resetTooltip,
            click: helpers.zoomToFeature
        });
    },

    showInfobox: function(e, countryInfo) {
        var formatnumber =function(number) {
            number = Number(number);
            if(isNaN(number)) return 0;
            let n = 0;
            let x = 3;
            var re = '\\d(?=(\\d{' + (x || 3) + '})+' + (n > 0 ? '\\.' : '$') + ')';
            return number.toFixed(Math.max(0, ~~n)).replace(new RegExp(re, 'g'), '$&,');
        };

        helpers.resetTooltip();
        var layer = e.target;
        var country = countryInfo.find(function(v){ return v.ISO3 === layer.feature.id;});
        var country_link = '';
    
        var country_url = (country.status < 4 && linkMap[layer.feature.id]) ? '/implementing_country/' + linkMap[layer.feature.id] + '':'';
        
        if(country_url === '') {
            country_link = '<strong> Country Page not available </strong>';
        }
        else
        {
            country_link = '<a href="' + country_url + '"><strong>Open Country Page</strong></a>';
        }

        var html = '<div>' +
            '<table class="country_info">' + 
            '  <thead><tr style="background-color:#f4f4f4"><th colspan="2"><img src="images/flags/gif/' + layer.feature.id.toLowerCase() + '.gif" style="margin:0px 10px 0px 5px"/>' + layer.feature.properties.name + '</th></tr></thead>' + 
            '  <tbody>' + '    <tr><td>GDP: ' + formatnumber(country.gdp) + ' USD </td><td>Population: ' + formatnumber(country.population) + '</td></tr>' + 
            '    <tr><td colspan="2">&nbsp;<strong>Country Commodity Total</strong></td></tr>' + 
            '    <tr><td><strong>' + formatnumber(country.resources_oil) + '</strong><img src="images/icon-dump/eiti_popup_oilunrefined.svg" style="margin:0px 2px 0px 2px;width:18px;"/> Oil </td>' + 
            '        <td></td>' + 
            '        </tr>' + 
            '    <tr><td></td>' + 
            '        <td></td></tr>' 
            + '    <tr><td colspan="2"><img src="images/icon-dump/eiti_popup_opencountry.svg" style="margin:0px 2px 0px 2px;width:18px"/>' +country_link+ '</td></tr>' + 
            '  </tbody>' + 
            '</table>' + 
            '</div>';

        var popup = L.popup({autoPan:true, closeButton:false, maxWidth:400})
            .setLatLng(e.latlng)
            .setContent(html)
            .openOn(layer._map);
    }

};

