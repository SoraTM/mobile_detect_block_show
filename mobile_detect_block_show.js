(function ($) {

/**
 * Provide the summary information for the Mobile Detect Block Show (Is Mobile) settings
 * vertical tab.
 */

Drupal.behaviors.MobileDetectBlockShowSettingsSummary = {
  attach: function (context) {

    $('fieldset#edit-mobile-detect-block-show', context).drupalSetSummary(function (context) {
      var vals = [];
      $('input[type="radio"]:checked', context).each(function () {
        vals.push($.trim($(this).next('label').text()));
      });
      if (!vals.length) {
        vals.push(Drupal.t('Not restricted'));
      }
      return vals.join(', ');
    });
  }
};

})(jQuery);