let React = require('react');
let d3 = require('d3');

let Chart = require('./Chart');
let Axis = require('./Axis');
let Bar = require('./Bar');
let Tooltip = require('./Tooltip');
let Legend = require('./Legend');

let DefaultPropsMixin = require('./DefaultPropsMixin');
let HeightWidthMixin = require('./HeightWidthMixin');
let ArrayifyMixin = require('./ArrayifyMixin');
let StackAccessorMixin = require('./StackAccessorMixin');
let StackDataMixin = require('./StackDataMixin');
let DefaultScalesMixin = require('./DefaultScalesMixin');
let TooltipMixin = require('./TooltipMixin');

let DataSet = React.createClass({
    propTypes: {
        data: React.PropTypes.array.isRequired,
        xScale: React.PropTypes.func.isRequired,
        yScale: React.PropTypes.func.isRequired,
        colorScale: React.PropTypes.func.isRequired,
        values: React.PropTypes.func.isRequired,
        label: React.PropTypes.func.isRequired,
        x: React.PropTypes.func.isRequired,
        y: React.PropTypes.func.isRequired,
        y0: React.PropTypes.func.isRequired
    },

    render() {
        let {data,
             xScale,
             yScale,
             colorScale,
             values,
             label,
             x,
             y,
             y0,
             onMouseEnter,
             onMouseLeave,
             groupedBars} = this.props;

        let bars;
        if (groupedBars) {
            bars = data.map((stack, serieIndex) => {
                return values(stack).map((e, index) => {
                    return (
                        <Bar
                            key={`${label(stack)}.${index}`}
                            width={xScale.rangeBand() / data.length}
                            height={yScale(yScale.domain()[0]) - yScale(y(e))}
                            x={xScale(x(e)) + ((xScale.rangeBand() * serieIndex) / data.length)}
                            y={yScale(y(e))}
                            fill={colorScale(label(stack))}
                            data={e}
                            onMouseEnter={onMouseEnter}
                            onMouseLeave={onMouseLeave}
                            />
                    );
                });
            });
        } else {
            bars = data.map(stack => {
                return values(stack).map((e, index) => {
                    return (
                        <Bar
                            key={`${label(stack)}.${index}`}
                            width={xScale.rangeBand()}
                            height={yScale(yScale.domain()[0]) - yScale(y(e))}
                            x={xScale(x(e))}
                            y={yScale(y0(e) + y(e))}
                            fill={colorScale(label(stack))}
                            data={e}
                            onMouseEnter={onMouseEnter}
                            onMouseLeave={onMouseLeave}
                            />
                    );
                });
            });
        }

        return (
                <g>{bars}</g>
        );
    }
});

let BarChart = React.createClass({
    mixins: [DefaultPropsMixin,
             HeightWidthMixin,
             ArrayifyMixin,
             StackAccessorMixin,
             StackDataMixin,
             DefaultScalesMixin,
             TooltipMixin],

    getDefaultProps() {
        return {
          colors:         d3.scale.category20(),
          colorAccessor:  (d, idx) => idx,
          legend:         false,
          legendPosition: 'right',
          sideOffset:     90
        };
    },

    _tooltipHtml(d, position) {
        let [xScale, yScale] = [this._xScale, this._yScale];

        let html = this.props.tooltipHtml(this.props.x(d),
                                          this.props.y0(d),
                                          this.props.y(d));

        let midPoint = xScale.rangeBand() / 2;
        let xPos = midPoint + xScale(this.props.x(d));

        let topStack = this._data[this._data.length - 1].values;
        let topElement = null;

        // TODO: this might not scale if dataset is huge.
        // consider pre-computing yPos for each X
        for (let i = 0; i < topStack.length; i++) {
            if (this.props.x(topStack[i]) === this.props.x(d)) {
                topElement = topStack[i];
                break;
            }
        }
        let yPos = yScale(this.props.y0(topElement) + this.props.y(topElement));

        return [html, xPos, yPos];
    },

    _renderLegend() {
        var props = this.props;
            
        if (props.legend) {      
          return (
            <Legend
              colors={props.colors}
              colorAccessor={props.colorAccessor}
              data={props.data}
              legendPosition={props.legendPosition}
              margins={props.margin}
              width={props.sideOffset} />
          );
        }
    },

    render() {
        let {height,
             width,
             margin,
             colorScale,
             values,
             label,
             y,
             y0,
             x,
             xAxis,
             yAxis,
             groupedBars} = this.props;

        let [data,
             innerWidth,
             innerHeight,
             xScale,
             yScale] = [this._data,
                        this._innerWidth,
                        this._innerHeight,
                        this._xScale,
                        this._yScale];

        return (
                <div>
                <Chart height={height} width={width} margin={margin}>
                <DataSet
            data={data}
            xScale={xScale}
            yScale={yScale}
            colorScale={colorScale}
            values={values}
            label={label}
            y={y}
            y0={y0}
            x={x}
            onMouseEnter={this.onMouseEnter}
            onMouseLeave={this.onMouseLeave}
            groupedBars={groupedBars}
                />

                <Axis
            className={"x axis"}
            orientation={"bottom"}
            scale={xScale}
            height={innerHeight}
            width={innerWidth}
            {...xAxis}
                />

                <Axis
            className={"y axis"}
            orientation={"left"}
            scale={yScale}
            height={innerHeight}
            width={innerWidth}
            {...yAxis}
                />
                { this.props.children }
                </Chart>

                <Tooltip {...this.state.tooltip}/>
                <div style={{ display: 'table-cell', width: this.props.sideOffset, 'verticalAlign': 'top' }}>
                    {this._renderLegend()}
                </div>
                </div>
        );
    }
});

module.exports = BarChart;
