var drupalPlaceholder = false;
if (!window.Drupal) {
  drupalPlaceholder = true;
  window.Drupal = {
    t: function(string) { return string; }
  };
}
Drupal.t('EITI Requirements');
Drupal.t('Level of Progress');
Drupal.t('Direction <br>of Progress');
Drupal.t('Categories');
Drupal.t('Requirements');
Drupal.t('<div><span>No Progress</span></div>');
Drupal.t('<div><span>Inadequate</span></div>');
Drupal.t('<div><span>Meaningful</span></div>');
Drupal.t('<div><span>Satisfactory</span></div>');
Drupal.t('<div><span>Beyond</span></div>');
Drupal.t('MSG oversight');
Drupal.t('Government engagement');
Drupal.t('Industry engagement');
Drupal.t('Civil society engagement');
Drupal.t('MSG governance');
Drupal.t('Workplan');
Drupal.t('Licenses and contracts');
Drupal.t('Legal framework');
Drupal.t('License allocations');
Drupal.t('License register');
Drupal.t('Policy on contract disclosure');
Drupal.t('Beneficial ownership');
Drupal.t('State participation');
Drupal.t('Monitoring production');
Drupal.t('Exploration data');
Drupal.t('Production data');
Drupal.t('Export data');
Drupal.t('Revenue collection');
Drupal.t('Comprehensiveness');
Drupal.t('In-kind revenues');
Drupal.t('Barter agreements');
Drupal.t('Transportation revenues');
Drupal.t('SOE transactions');
Drupal.t('Direct subnational payments');
Drupal.t('Disaggregation');
Drupal.t('Data timeliness');
Drupal.t('Data quality');
Drupal.t('Revenue allocation');
Drupal.t('Revenue management and expenditures');
Drupal.t('Subnational transfers');
Drupal.t('Distribution of revenues');
Drupal.t('Socio-economic contribution');
Drupal.t('Mandatory social expenditures');
Drupal.t('Discretionary social expenditures');
Drupal.t('SOE quasi-fiscal expenditures');
Drupal.t('Economic contribution');
Drupal.t('Outcomes and impact');
Drupal.t('Public debate');
Drupal.t('Data accessibility');
Drupal.t('Follow up on recommendations');
Drupal.t('Outcomes and impact of implementation');
Drupal.t('<strong>No progress.</strong> All or nearly all aspects of the requirement remain outstanding and the broader objective of the requirement is not fulfilled.');
Drupal.t('<strong>Inadequate progress.</strong> Significant aspects of the requirement have not been implemented and the broader objective of the requirement is far from fulfilled.');
Drupal.t('<strong>Meaningful progress.</strong> Significant aspects of the requirement have been implemented and the broader objective of the requirement is being fulfilled.');
Drupal.t('<strong>Satisfactory progress.</strong> All aspects of the requirement have been implemented and the broader objective of the requirement has been fulfilled.');
Drupal.t('<strong>Beyond.</strong> The country has gone beyond the requirements.');
Drupal.t('This requirement is only encouraged or recommended and should not be taken into account in assessing compliance.');
Drupal.t('The MSG has demonstrated that this requirement is not applicable in the country.');
Drupal.t('Direction of progress');
Drupal.t('No change in performance since the last Validation.');
Drupal.t('The country is performing worse that in the last Validation.');
Drupal.t('The country is performing better than in the last Validation.');
Drupal.t('Overall assessment');

if (drupalPlaceholder) {
  Drupal = null;
}
export var translations = {};
