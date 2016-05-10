
import _ from 'underscore';

export var helpers = {
    getBasePath: function() {
        return window.Drupal && window.Drupal.settings && window.Drupal.settings.eitiMapWidgetsLibPath ? window.Drupal.settings.eitiMapWidgetsLibPath : 'dist';
    },

    getEndPoint: function() {
        return window.Drupal ? '/api/v1.0/implementing_country' : 'source/scripts/data/implementing_country.json';   
    }, 

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
            if(feature.indicator_color) {
                return feature.indicator_color;
            }
            else
            {
                return '#dddddd';
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

    showTooltipStatus: function (e, countryInfo) {
        var layer = e.target;

        var country = _.find(countryInfo, function(v){ return v.iso3 === layer.feature.id;});
        var country_link = '';


        if(country) {
            country_link = '<a href="/implementing_country/' +  country.id + '"><strong>' + layer.feature.properties.name + '</strong></a>';
        }
        else
        {
            country_link = '<strong>' + layer.feature.properties.name + '</strong>';
        }
        e.latlng.lat = e.latlng.lat+2.5;
        var popup = L.popup({autoPan:false, closeButton:false})
            .setLatLng(e.latlng)
            .setContent(country_link)
            .openOn(layer._map);
    },

    resetTooltip: function(e) {
    // Left for future reference
    },

    zoomToFeature: function(e, countryInfo){
        var layer = e.target;
        var country = _.find(countryInfo, function(v){ return v.iso3 === layer.feature.id;});
        window.location = '/implementing_country/' +  country.id;
    },

    // Helper function that can translate strings.
    t: function(string) {
        // Check if window.Drupal.t() exists and call it.
        if (window.Drupal && typeof window.Drupal.t === 'function') {
            return window.Drupal.t(string);
        }
        return string;
    },

    findFormatValue: function(data, condition) {
        var object = data.find(condition);
        var value = object ? this.formatNumber(object.value) : this.t('n/a');
        return value;
    },

    showInfobox: function(e, countryInfo) {
        helpers.resetTooltip();

        var layer = e.target;
        var country = _.find(countryInfo, function(v){ return v.iso3 === layer.feature.id;});
        var country_link = '';

        var country_url = '/implementing_country/' +  country.id;

        if(country_url === '') {
            country_link = '<strong>' + this.t('Country Page not available') + '</strong>';
        }
        else {
            country_link = '<a href="' + country_url + '"><strong>' + this.t('Open Country Page') + '</strong></a>';
        }

        // General info
        var years = Object.keys(country.reports);
        var last = _.last(years);
        var yearData = country.reports[last];

        // Prepare data for info box

        // Status
        var country_status = country.status ? country.status.name : this.t('n/a');

        // Member Since
        var memberDate = (country.status_date || country.status_date !== null) ? new Date(country.status_date*1000) : undefined;
        var country_member_since = memberDate ? memberDate.getFullYear() : t.this('n/a');

        // Latest Report Year
        var country_last_report_year = last;
        
        // Latest Report Link
        var country_last_report_file = country.annual_report_file;

        // Extractives Revenue latest year
        
        var indicator_government_revenue = yearData.find(function(v){ return (v.commodity === "Extractives")}) || yearData.find(function(v){ return (v.commodity === "Government revenue - extractive industries")}) || undefined;
        if(indicator_government_revenue) {
            var years_revenue = Object.keys(country.revenues);
            var last_revenue = _.last(years_revenue);
            var yearData_revenue = country.revenues[last_revenue];
            indicator_government_revenue = yearData_revenue.government;
        }
        indicator_government_revenue = indicator_government_revenue || 'n/a';

        // Sectors Covered

        // Number of companies reporting

        // Online Licenses (link)[Oil], (link)[Mining]
        var years_licenses = country.licenses ? Object.keys(country.licenses):[];
        var last_licenses = _.last(years_licenses);
        var indicator_licenses = country.licenses ? country.licenses[last_licenses] : undefined;


        // Online Contract (link)
        var years_contracts = country.contracts ? Object.keys(country.contracts):[];
        var last_contracts = _.last(years_contracts);
        var indicator_contracts = country.contracts ? country.contracts[last_contracts]: undefined;

        // Country Website
        var country_website = country.local_website ? country.local_website : this.t('n/a');

        var currency_code = 'USD';
        var info_header = '';
        var info_content_first = '';
        var info_top_indicators_first = '';
        var info_content_second = '';
        var info_top_indicators_second = '';
        var info_content_third = '';
        var info_content_second_a = '';

        // Add country info.
        info_header = info_header +
            '<img src="' + this.getResourceUrl('images/flags/gif/' + layer.feature.id.toLowerCase() + '.gif') + '" style=""/>' +
            '<span>' + layer.feature.properties.name + '</span>';

        // Add Status indicator info.
        info_top_indicators_first = info_top_indicators_first +
            '<span class="info">' +
            '  <span class="label">' + this.t('Status') + ':</span> <span class="value"><strong>' + country_status + '</strong></span>' +
            '</span>';

        // Add Last Year indicator info.
        info_top_indicators_first = info_top_indicators_first +
            '<span class="info">' +
            '  <span class="label">' + this.t('Joined in') + ':</span> <span class="value"><strong>' + country_member_since + '</strong></span>' +
            '</span>';

        // Add Last Report Link
        info_top_indicators_second = info_top_indicators_second +
            '<span class="info">' +
            '  <span class="label">' + this.t('Latest EITI Report covers') + ':</span> <span class="value"><a href="' + (country_last_report_file ? "#": country_last_report_file) + '">' + country_last_report_year + '</a></span>' +
            '</span>';

        // Add Revenue
        info_content_first = info_content_first +
            '<div class="info-block">' +
            '<span class="info">' +
            '  <span class="label">' + this.t('Extractives revenues for ') + last +':</span> <span class="value">' + this.formatNumber(indicator_government_revenue) + ' ' + currency_code + '</span>' +
            '</span>' +
            '</div>';

        // Add Sectors Covered
        info_content_second = info_content_second +
            '<div class="info-block">' +
            '<span class="info">' +
            '   <span class="label">' + this.t('Sectors covered') + ':</span>' +
            '   <span class="value">Oil <img class="icon" src="' + this.getResourceUrl('images/icon-dump/eiti_popup_oilrefined.svg') + '" alt="Oil Icon" /></span>' +
            '   <span class="value">Gas <img class="icon" src="' + this.getResourceUrl('images/icon-dump/eiti_popup_oilunrefined.svg') + '" alt="Oil Icon" /></span>' +
            '   <span class="value">Mining <img class="icon" src="' + this.getResourceUrl('images/icon-dump/eiti_popup_mineral.svg') + '" alt="Oil Icon" /></span>' +
            '</span>' +
            '</div>';
        // Add Companies reporting
        info_content_second_a = info_content_second_a + '<div class="info-block">' +
            '<span class="info">' +
            '  <span class="label">' + this.t('Number of companies reporting') + ':</span> <span class="value">' + 32 + '</span>' +
            '</span>' +
            '</div>';
        // Add info about Online Licenses.
        info_content_third = '<div class="info-block">' +
            '  <span class="label">' + this.t('Online Licenses') + ':</span>' +
            '  <span class="value">' + (indicator_licenses ? '<a href="' +indicator_licenses[0]+ '" target="_blank">' + this.t('Yes') + '</a>' : this.t('No')) + '</span>' +
            '</div>';

        // Add info about Online Contracts.
        info_content_third = info_content_third +
            '<div class="info-block">' +
            '  <span class="label">' + this.t('Online Contracts') + ':</span>' +
            '  <span class="value">' + (indicator_contracts ? '<a href="' +indicator_contracts[0]+ '" target="_blank">' + this.t('Yes') + '</a>' : this.t('No')) + '</span>' +
            '</div>';

        var html = '<aside class="country-info-wrapper">' +
            '<div class="country-info-header">' + info_header + '</div>' +
            '<div class="country-info-top-indicators">' + info_top_indicators_first + '</div>' +
            '<div class="country-info-top-indicators">' + info_top_indicators_second + '</div>' +
            '<div class="country-info-content">' + info_content_first + '</div>' +
            '<div class="country-info-content">' + info_content_second + '</div>' +
            '<div class="country-info-content">' + info_content_second_a + '</div>' +
            '<div class="country-info-content">' + info_content_third + '</div>' +
            '<div class="country-link">' + '<img class="country-icon" src="' + this.getResourceUrl('images/icon-dump/eiti_popup_opencountry.svg') + '" /> ' + country_link + '</div>' +
            '</aside>';

        var popup = L.popup({autoPan:true, closeButton:false, maxWidth:400})
            .setLatLng(e.latlng)
            .setContent(html)
            .openOn(layer._map);
    },

    formatNumber: function(number) {
        number = Number(number);
        if(isNaN(number)) return 0;
        let n = 0;
        let x = 3;
        var re = '\\d(?=(\\d{' + (x || 3) + '})+' + (n > 0 ? '\\.' : '$') + ')';
        return number.toFixed(Math.max(0, ~~n)).replace(new RegExp(re, 'g'), '$&,');
    },

    getResourceUrl: function(relative_path) {
        return this.getBasePath() + '/' + relative_path;
    }
};
