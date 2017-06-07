var drupalPlaceholder = false;
if (!window.Drupal) {
  drupalPlaceholder = true;
  window.Drupal = {
    t: function(string) { return string; }
  };
}

Drupal.t('<br>For an overview of the former status of countries under the EITI Rules, click <a href="/countries-archive">here</a>.<br>For a list of former members or countries who are preparing to join, click <a href="/countries/other">here</a>.<br><br>');
Drupal.t('Available');
Drupal.t('Click on a country to find out more');
Drupal.t('Coal');
Drupal.t('Coal, tons');
Drupal.t('Copper');
Drupal.t('Copper, tons');
Drupal.t('Extractive industry revenues');
Drupal.t('Gas');
Drupal.t('Gas, volume');
Drupal.t('Gold');
Drupal.t('Gold, tons');
Drupal.t('Government extractives revenue');
Drupal.t('Government revenue - extractive industries');
Drupal.t('hide');
Drupal.t('Implementation status');
Drupal.t('Inadequate progress / suspended<br>');
Drupal.t('Joined in');
Drupal.t('Latest EITI Report covers');
Drupal.t('Meaningful progress');
Drupal.t('Mining');
Drupal.t('Number of companies reporting');
Drupal.t('Oil');
Drupal.t('Oil, volume');
Drupal.t('Online Contracts');
Drupal.t('Online Licenses');
Drupal.t('Online mining registry');
Drupal.t('Online oil registry');
Drupal.t('Online registry of contracts');
Drupal.t('Open Country Page');
Drupal.t('Open Local EITI Website');
Drupal.t('Overview');
Drupal.t('Overview on how countries are progressing towards meeting the 2016 EITI Standard. <br><a href="/about/how-we-work#upholding-the-standard-internationally-validation">Country statuses explained</a>');
Drupal.t('Revenues per capita');
Drupal.t('Satisfactory progress');
Drupal.t('Sectors covered');
Drupal.t('Share of revenues');
Drupal.t('show');
Drupal.t('Source: EITI summary data');
Drupal.t('Status');
Drupal.t('Suspended due to political instability');
Drupal.t('Suspended for missing deadline');
Drupal.t('Unavailable');
Drupal.t('USD');
Drupal.t('Yes');
Drupal.t('Yet to be assessed against the 2016 Standard<br>');
Drupal.t('Tax & Legal Framework');
Drupal.t('Production');
Drupal.t('Revenues');

if (drupalPlaceholder) {
  Drupal = null;
}
export var translations = {};
